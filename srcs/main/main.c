/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:36:49 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/22 23:07:10 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"
#include "../../includes/execution.h"
#include "../../includes/minishell.h"

int	g_exit_code = 0;

int	minishell_atty(t_shared_info *info)
{
	char	*line;
	int		flag;

	flag = 0;
	while (true)
	{
		setup_signal_prompt();
		line = handle_prompt(info->envp);
		if (!line)
			builtin_exit(info);
		if (export_exit_code(g_exit_code, flag, info) == FAILUER)
			return (FAILUER);
		info->branch = parser(line, info->envp);
		free(line);
		if (!info->branch)
			continue ;
		setup_signal_exec();
		flag = exec_manage(info->branch, info, 0, 1);
		free_tree_rec(&info->branch);
		g_exit_code = detect_ecode(flag, info);
		info->pipe = false;
	}
	return (flag);
}

int	minishell_pipe(t_shared_info *info)
{
	char	*line;
	int		flag;

	line = get_line(STDIN_FILENO);
	if (!line)
		return (FAILUER);
	info->branch = parser(line, info->envp);
	free(line);
	if (!info->branch)
		return (FAILUER);
	setup_signal_exec();
	flag = exec_manage(info->branch, info, 0, 1);
	g_exit_code = detect_ecode(flag, info);
	if (export_exit_code(g_exit_code, flag, info) == FAILUER)
		return (FAILUER);
	builtin_exit(info);
	return (flag);
}

int	main(int argc, char **argv, char **envp)
{
	t_shared_info	info;
	int				flag;

	info = collect_info(envp);
	if (!info.envp)
		return (EXIT_FAILURE);
	if (!isatty(STDIN_FILENO))
		flag = minishell_pipe(&info);
	else
		flag = minishell_atty(&info);
	t_lstclear(&info.envp, free);
	(void)argc;
	(void)argv;
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
