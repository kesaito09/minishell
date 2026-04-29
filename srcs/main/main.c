/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:36:49 by natakaha          #+#    #+#             */
/*   Updated: 2026/04/19 22:00:00 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"
#include "../../includes/execution.h"
#include "../../includes/minishell.h"

int g_signal_code = 0;

static int minishell_atty(t_shared_info *info);
static int minishell_pipe(t_shared_info *info);
static int whole_proc(t_shared_info *info);

int main(int argc, char **argv, char **envp) {
  t_shared_info info;

  info = collect_info(envp);
  if (!isatty(STDIN_FILENO))
    minishell_pipe(&info);
  else
    minishell_atty(&info);
  builtin_exit(NULL, &info);
  (void)argc;
  (void)argv;
}

static int whole_proc(t_shared_info *info) {
  int flag;

  info->branch = parser(info);
  setup_signal_exec();
  flag = exec_manage(info->branch, info, 0, 1);
  free_tree_rec(&info->branch);
  info->last_ecode = detect_ecode(flag, info);
  env_exit_code(info->last_ecode, flag, info);
  info->pipe = false;
  return (flag);
}

static int minishell_atty(t_shared_info *info) {
  char *input;
  int flag;

  flag = 0;
  print_logo();
  while (true) {
    setup_signal_prompt();
    input = handle_prompt(info->envp);
    if (!input)
      builtin_exit(NULL, info);
    if (!*input) {
      env_exit_code(0, SUCCESS, info);
      continue;
    }
    info->input = script_split(input);
    free(input);
    if (!info->input)
      fatal_exit(info);
    while (info->input && info->input->token)
      whole_proc(info);
  }
  return (flag);
}

static int minishell_pipe(t_shared_info *info) {
  char *input;
  int flag;

  input = get_line(STDIN_FILENO);
  if (!input)
    fatal_exit(info);
  info->input = script_split(input);
  free(input);
  if (!info->input)
    fatal_exit(info);
  while (info->input && info->input->token)
    flag = whole_proc(info);
  return (flag);
}
