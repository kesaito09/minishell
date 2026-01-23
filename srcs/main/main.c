/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:36:49 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/23 11:28:07 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"
#include "../../includes/execution.h"
#include "../../includes/minishell.h"

int	g_exit_code = 0;

static int	minishell_atty(t_shared_info *info);
static int	minishell_pipe(t_shared_info *info);
static int	whole_proc(t_shared_info *info);

int	main(int argc, char **argv, char **envp)
{
	t_shared_info	info;

	info = collect_info(envp);
	if (!info.envp)
		return (EXIT_FAILURE);
	if (!isatty(STDIN_FILENO))
		minishell_pipe(&info);
	else
		minishell_atty(&info);
	t_lstclear(&info.envp, free);
	(void)argc;
	(void)argv;
}

static int	whole_proc(t_shared_info *info)
{
	int	flag;

	info->branch = parser(info);
	if (!info->branch)
		return (FAILUER);
	setup_signal_exec();
	flag = exec_manage(info->branch, info, 0, 1);
	free_tree_rec(&info->branch);
	g_exit_code = detect_ecode(flag, info);
	return (flag);
}

static int	minishell_atty(t_shared_info *info)
{
	char	*input;
	int		flag;

	flag = 0;
	while (true)
	{
		setup_signal_prompt();
		input = handle_prompt(info->envp);
		if (!input)
			builtin_exit(info);
		if (export_exit_code(g_exit_code, flag, info) == FAILUER)
			return (FAILUER);
		info->input = script_split(input);
		free(input);
		if (!info->input)
			return (FAILUER);
		while (info->input)
			whole_proc(info);
		info->pipe = false;
	}
	return (flag);
}

static int	minishell_pipe(t_shared_info *info)
{
	char	*input;
	int		flag;

	input = get_line(STDIN_FILENO);
	if (!input)
		return (FAILUER);
	info->input = script_split(input);
	free(input);
	if (!info->input)
		return (FAILUER);
	while (info->input)
		flag = whole_proc(info);
	if (export_exit_code(g_exit_code, flag, info) == FAILUER)
		return (FAILUER);
	builtin_exit(info);
	return (flag);
}


// /*tester*/

//int main(int argc, char **argv, char **envp)
//{
//	t_tree	*branch;
//	t_shared_info	info;

//	if (argc < 2)
//		return (0);
//	info = correct_info(envp);
//	branch = parser(argv[1]);
//	exec_manage(branch, &info, 0, 1);
//	free_tree_rec(branch);
//	free_split(info.path);
//	wait_pidlist(info.plist);
//	free_pid(info.plist);
//}

//int	main(void)
//{
//	while(1);
//}
