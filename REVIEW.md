# minishell レビュー（subject 直結項目）

- 対象: `/Users/naoki/development/00_42projects/minishell`
- 日付: 2026-04-30
- 観点ソース: `minishell.pdf` Chapter IV (Mandatory) + Chapter VI (Bonus)
- 検証方法: PDF 要件突き合わせ + 80+ ケース bash 比較 + ソース監査
- 原則: **「subject にないものは不要」**、**「曖昧なら bash を参照」**
- 重大警告: **mandatory が perfect でないと bonus は評価対象外**（subject 明記）

---

## 0. サマリー

| # | 項目 | 重大度 | 修正規模 |
|---|---|---|---|
| 1 | `cd` 引数なしで HOME を stdout に出力 | 高 | 1 行削除 |
| 2 | `exit` のパース系（オーバーフロー / 空 / 符号 / 引数複数） | 高 | 中（自前 strtoll） |
| 3 | 未閉鎖 quote 検出時の exit code が 0（bash は 2） | 高 | 数行 |
| 4 | プロンプト中 SIGINT で `$?=130` にならない | 高 | 4 行追加 |
| 5 | heredoc 中 Ctrl-C のハンドリング破綻 | 高 | 中 |
| 6 | `export` の部分エラーで残り引数を処理しない | 高 | 5 行 |

---

## 1. ✅ Subject 要件の充足確認

| Subject 要件 | 状態 | 根拠 |
|---|---|---|
| Global 変数は最大 1 個 | ✅ | `srcs/main/main.c:17` の `g_signal_code` のみ |
| Global は signal number のみ格納 | ✅ | `signal.c:19` で `= 2` を入れるだけ |
| Display a prompt | ✅ | `handle_prompt` |
| Working history | ✅ | `srcs/main/input.c:34` で `add_history` |
| `\` と `;` を解釈しない | ✅ | lexer で OPERATOR に含めず |
| 未閉鎖 quote を解釈しない | ⚠️ | エラーは出すが exit code 0（後述 #3） |
| `'` / `"` のメタ抑止（`"` は `$` のみ展開） | ✅ | 実測 OK |
| `<`, `>`, `<<`, `>>` | ✅ | 多重 redirect の全 truncate も含めて OK |
| `\|` パイプ | ✅ | 多段 + builtin in subshell も OK |
| `$VAR` 展開 | ✅ | 実測 OK |
| `$?` 展開 | ✅ | 実測 OK |
| ctrl-D でシェル終了 | ✅ | EOF で rc=0 終了 |
| ctrl-\\ does nothing | ✅ | `setup_signal_prompt` で `SIG_IGN` |
| ctrl-C で新プロンプト | ⚠️ | 改行+プロンプトは出るが `$?=130` にならない（後述 #4） |
| echo `-n` | ✅ | `-nnnn` / `-n -n` / `"-n"` 全 OK |
| cd (relative/absolute) | ⚠️ | 引数なしで HOME を出力（後述 #1） |
| pwd / env / unset | ✅ | 動作 OK |
| export | ⚠️ | 部分エラー時に残り引数を処理しない（後述 #6） |
| exit | ⚠️ | パース系に複数バグ（後述 #2） |
| segfault しない | ✅ | mini_death 系入力サンプルで segv 確認なし |
| Bonus: `&&`/`\|\|`/`()` + wildcards | ✅ | 実装済み |

---

## 2. ❌ Subject 違反（必ず修正）

### #1. `cd` 引数なしで HOME を stdout に出力している

**Subject**: `cd with only a relative or absolute path`（出力する仕様は無い）
**bash**: `cd` は何も出さない

**再現**:
```
$ printf 'cd && pwd\nexit\n' | ./minishell
/Users/naoki   ← 余計な行
/Users/naoki
```

**箇所**: `srcs/builtin_cmd/cmd_cd.c:48`
```c
static char *resolve_cd_path(t_token *node, t_shared_info *info, char **key)
{
    ...
    if (*key)  // *key は "HOME" or "OLDPWD"
    {
        path = return_value(*key, info->envp);
        if (!path)
            fatal_exit(info);
        ft_putendl_fd(path, 1);   // ← cd 引数なしでも HOME を 1 行出力
    }
    ...
}
```

**修正案**: subject は `cd` の出力を要求していないので **行ごと削除** が安全。
```c
if (*key)
{
    path = return_value(*key, info->envp);
    if (!path)
        fatal_exit(info);
}
```

---

### #2. `exit` のパース系バグ

**Subject**: `exit with no options` + bash 参照
**箇所**: `srcs/builtin_cmd/cmd_exit.c` + `libft/ft_libc/ft_atoi.c`

| 入力 | minishell | bash | 原因 |
|---|---|---|---|
| `exit 9223372036854775808` | rc=0 (silent overflow) | rc=255 + numeric error | `ft_atoi` が `int` 返却、LLONG オーバーフロー検出無し |
| `exit ""` | rc=0 (0 と扱う) | rc=255 + numeric error | `ft_isnumber` が空文字を true 判定 |
| `exit "+100"` | rc=255 + numeric error | rc=100 | `ft_isnumber` が `+` を非 digit 判定 |
| `exit hello 1` | rc=1 + シェル**継続** | rc=255 + シェル**終了** | 1 個目が非数値なら exit すべき判定が無い |

**修正案**:
1. 自前の long long パーサを実装
   - `+`/`-` を **1 個まで**許容、後ろに digit が **1 個以上**必須
   - 桁ごとに `LLONG_MAX/MIN` 検査
   - オーバーフロー / 不正形式 → 失敗
2. 引数複数時は **1 個目を先に数値判定** してから分岐
   - 数値: `too many args` を出して `last_ecode=1` でシェル**継続**
   - 非数値: `numeric required` を出して `last_ecode=2` でシェル**終了**

---

### #3. 未閉鎖 quote 検出時の exit code が 0

**Subject**: 「Not interpret unclosed quotes」
**bash**: unclosed quote は構文エラー → rc=2

**再現**:
```
$ printf 'echo "hello\nexit\n' | ./minishell
minishell: syntax error: unclosed quote
$ echo $?
0   ← bash は 2
```

**修正案**: lexer/parser の unclosed quote 検出パスで
```c
info->last_ecode = 2;
```
をセットしてから次のプロンプトへ戻る。

---

### #4. プロンプト中 SIGINT で `$?=130` にならない

**Subject**: 「ctrl-C displays a new prompt on a new line」+ 「`$?` should expand to the exit status of the most recently executed foreground pipeline」+ bash 参照

**箇所**: `srcs/main/signal.c:19`
```c
static void handle_sigint_prompt(int sig)
{
    (void)sig;
    g_signal_code = 2;   // ← ここでセット
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}
```

**問題**: `g_signal_code` は **セットされるだけで誰も読んでいない**。
`grep -rn g_signal_code srcs/` で setter のみ、reader ゼロ。

**修正案**: メインループ（`whole_proc` 冒頭または `parser` 直前）に
```c
if (g_signal_code) {
    info->last_ecode = 130;
    env_exit_code(130, SUCCESS, info);
    g_signal_code = 0;
}
```

---

### #5. heredoc 中 Ctrl-C のハンドリング破綻

**Subject**: 「ctrl-C bash like」+ 「`<<` should be given a delimiter, then read the input until a line containing the delimiter is seen」+ bash 参照
**bash**: heredoc 中 ctrl-C で heredoc 中止 + `$?=130` + 後続コマンド実行スキップ

**箇所**: `srcs/execution/core_heredoc.c:41`
```c
if (heardoc_fork(...) == FAILURE)   // FAILURE = -1
```

**問題**: `heardoc_fork` は SIGINT 検出時に `pid_fix()` 経由で **130** を返すが、`FAILURE = -1` 比較にマッチせず**成功扱い**になっている。
根因: `SUCCESS=1 / FAILURE=-1` の独自定義と、数値 exit code（0/1/2/130）の混同。

**修正案**:
1. `heardoc_fork` の戻り値を bool 二値化
2. SIGINT 検出時は `info->last_ecode = 130` をセットしてから FAILURE を返す
3. `heredoc()` 戻り値 NULL を `srcs/parser/parse1_cmd.c:66` 周辺で検出して parse 中断
4. 中断時は `whole_proc` で実行をスキップ

---

### #6. `export` の部分エラー継続なし

**Subject**: `export with no options` + bash 参照
**bash**: 不正引数の前後で valid な引数は登録、最終 rc=1

**再現**:
```
$ printf 'export A=1 BAD- B=2 && echo $A:$B\nexit\n' | bash
1:2

$ printf 'export A=1 BAD- B=2 && echo $A:$B\nexit\n' | ./minishell
(B=2 が登録されない)
```

**箇所**: `srcs/builtin_cmd/cmd_export.c:21-33`
```c
while (cmd) {
    flag = export_module(cmd, info, BOTTOM, 0);
    if (!flag)
        return (invalid_message(cmd->token), FAILURE);  // 即 return
    cmd = cmd->next;
}
```

**修正案**:
```c
int flag = SUCCESS;
while (cmd) {
    if (!export_module(cmd, info, BOTTOM, 0)) {
        invalid_message(cmd->token);
        flag = FAILURE;
    }
    cmd = cmd->next;
}
return (flag);
```

---

## 3. 残作業として確認推奨

### A. メモリリーク

**Subject**: 「The readline() function may cause memory leaks, but you are not required to fix them. However, this does not mean your own code, yes the code you wrote, can have memory leaks.」

確認方法:
- macOS: `MallocStackLogging=1 leaks --atExit -- ./minishell < input.txt`
- Linux: `valgrind --leak-check=full --suppressions=readline.supp ./minishell`

readline 起因は除外可。自コード由来のリークは subject 違反。

### B. mini_death 系の網羅 segv 検査

サンプル入力で segv なしを確認済みだが、`zstenger93/42_minishell_tester` の `mini_death/1_segfault.sh` を直接流して全網羅すること。

```bash
git clone https://github.com/zstenger93/42_minishell_tester ~/tester
cd ~/tester && bash tester.sh m   # mandatory
bash tester.sh d                  # mini_death (segv 専用)
```

---

## 4. 修正順序

評価ゲートを通すための最小順序（上から潰す）:

1. **#1 cd 引数なしの出力削除** — 1 行削除、即効性高
2. **#6 export 部分エラー継続** — while ループ修正、5 行
3. **#2 exit パース修正** — 自前 strtoll、数値判定リライト、20-30 行
4. **#3 未閉鎖 quote の rc=2** — lexer エラー経路で `last_ecode = 2`
5. **#4 プロンプト SIGINT で `$?=130`** — メインループに 4 行追加
6. **#5 heredoc Ctrl-C のシグナル伝搬** — 戻り値の意味整理、中規模リファクタ

1〜5 は局所修正で半日。6 は SUCCESS/FAILURE 命名と signal 戻り値の整理が要るので慎重に。

その後 **A. リーク確認** → **B. mini_death 走破** で評価対策完了。

---

## 5. Subject 範囲外として除外した項目

以下は subject に明記がなく、「Anything that is not asked is not required」原則で**修正不要**:

- word splitting（`echo $X` で X="a b" を 2 引数に分割）
- `<<<` の clean syntax error（`<<<` は subject 範囲外、segv なければ OK）
- `${VAR}` ブレース展開
- SHLVL の範囲チェック（負値・1000 超）
- `cd` 多引数の `too many arguments` メッセージ
- `echo -` 単独のリテラル化
- `$$`, `$_`, `$0` などの位置パラメータ
- `env` の引数あり対応
- `export` 単独表示の `declare -x` 形式（subject `no options`）
- command not found メッセージの prefix 整形
- heredoc 三重 open の最適化（内部実装）
- `SUCCESS=1` / `FAILURE=-1` の独自定義（内部実装、ただし #5 の根因なので一緒に整理推奨）
