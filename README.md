*This project has been created as part of the 42 curriculum by kesaitou, natakaha.*

# minishell

## Description

`minishell` is a small, POSIX-style shell written in C as part of the 42 curriculum.
The goal of the project is to deepen our understanding of process management
(`fork`, `execve`, `wait*`) and file descriptors (`pipe`, `dup2`, redirections)
by re-implementing the core behavior of `bash` from scratch.

The shell offers an interactive REPL with a prompt and command history (via GNU
Readline), tokenizes user input, parses it into an abstract syntax tree, and
executes commands by spawning processes and managing their I/O.

Mandatory features:

- Interactive prompt with working history.
- Lookup of executables through `PATH`, relative paths, and absolute paths.
- Single global variable used only to carry a received signal number.
- Single quotes `'…'` and double quotes `"…"` (with `$` expansion inside `"`).
- Redirections `<`, `>`, `<<` (heredoc, no history), and `>>` (append).
- Pipes `|` connecting the stdout of one command to the stdin of the next.
- Environment variable expansion (`$VAR`) and last exit status (`$?`).
- Signal handling for `Ctrl-C`, `Ctrl-D`, and `Ctrl-\` matching bash semantics
  in interactive mode.
- Built-ins: `echo` (with `-n`), `cd` (relative/absolute), `pwd`, `export`,
  `unset`, `env`, `exit`.

Bonus features:

- Logical operators `&&` and `||` with parenthesized precedence `( … )`.
- Wildcard `*` expansion against the current working directory.

## Instructions

### Requirements

- A Unix-like environment (Linux or macOS).
- A C toolchain providing `cc` (Clang or GCC).
- GNU Readline development headers and library.
    - macOS (Homebrew): `brew install readline` — the Makefile auto-detects
      `brew --prefix readline` and adds the include and library paths.
    - Debian/Ubuntu: `sudo apt install libreadline-dev`.
- `make`.

### Build

From the project root:

```sh
make            # builds ./minishell (and libft.a as a dependency)
make re         # full rebuild
make clean      # remove object files
make fclean     # remove object files, libft.a, and ./minishell
```

The Makefile compiles every translation unit with `-Wall -Wextra -Werror`,
links the bundled `libft/` archive, and links GNU Readline.

### Run

```sh
./minishell
```

You will be greeted by an ASCII logo and the `minishell$ ` prompt. Type any
supported command. To leave the shell, run `exit` or press `Ctrl-D` on an
empty prompt.

The shell also accepts a script through standard input for non-interactive
execution:

```sh
./minishell < some_script.sh
echo 'echo hello | cat' | ./minishell
```

## Resources

### Documentation and references

- `bash(1)` and the GNU Bash manual
  (<https://www.gnu.org/software/bash/manual/>) — reference shell whose
  behavior we mirror whenever the subject is silent.
- POSIX.1-2017 *Shell Command Language*
  (<https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html>)
  — grammar and quoting/expansion semantics.
- GNU Readline documentation
  (<https://tiswww.case.edu/php/chet/readline/readline.html>) — line editing,
  history, `rl_*` helpers used during signal handling.
- Linux man pages we relied on heavily: `fork(2)`, `execve(2)`, `pipe(2)`,
  `dup2(2)`, `waitpid(2)`, `signal(7)`, `sigaction(2)`, `tcsetattr(3)`,
  `access(2)`, `stat(2)`, `getcwd(3)`, `chdir(2)`, `unlink(2)`.
- Stephen Brennan, *Write a Shell in C*
  (<https://brennan.io/2015/01/16/write-a-shell-in-c/>) — used as a starting
  reference for the REPL/exec skeleton.
- 42 *Norm* (`norminette`) coding standard, applied to every source file.

### Use of AI

AI assistants were used to support refactoring, test-case generation, and
verification of behavior against the `bash` specification. All code was
written, reviewed, and integrated by the authors.

## Repository layout

```
minishell/
├── Makefile      # build rules (NAME, all, clean, fclean, re)
├── includes/     # public headers (*.h)
├── srcs/
│   ├── main/         # entry point, prompt loop, signal setup
│   ├── lexer/        # tokenizer + token list helpers
│   ├── parser/       # AST builder (parse_command/pipe/logical)
│   ├── expander/     # quote handling, $VAR/$?, wildcards
│   ├── execution/    # fork/exec, pipes, redirections, heredoc
│   └── builtin_cmd/  # echo, cd, pwd, export, unset, env, exit
└── libft/        # 42 standard helpers (bundled, built first)
```

## Built-ins quick reference

| Builtin  | Supported options / scope         |
| -------- | --------------------------------- |
| `echo`   | `-n` flag                         |
| `cd`     | Absolute and relative paths       |
| `pwd`    | No options                        |
| `export` | No options                        |
| `unset`  | No options                        |
| `env`    | No options, no arguments          |
| `exit`   | No options (numeric arg accepted) |