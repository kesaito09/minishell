/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:36:49 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/21 04:29:29 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main.h"
#include "../../includes/execution.h"
#include "../../includes/minishell.h"

int	minishell_atty(t_shared_info *info)
{
	char	*line;
	t_tree	*branch;
	int		flag;

	while (true)
	{
		setup_signal_prompt();
		line = handle_prompt();
		if (!line)
			return (SUCCESS);
		branch = parser(line, info->envp);
		free(line);
		if (!branch)
			continue ;
		setup_signal_exec();
		flag = exec_manage(branch, info, 0, 1);
		free_tree_rec(branch);
		info->ecode = detect_ecode(flag, info);
		if (export_exit_code(info->ecode, flag, info) == FAILUER)
			return (FAILUER);
		info->pipe = false;
	}
	return (flag);
}

int	minishell_pipe(t_shared_info *info)
{
	char	*line;
	t_tree	*branch;
	int		flag;

	line = get_line(STDIN_FILENO);
	if (!line)
		return (FAILUER);
	branch = parser(line, info->envp);
	if (!branch)
		return (free(line), FAILUER);
	flag = exec_manage(branch, info, 0, 1);
	free_tree_rec(branch);
	free(line);
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
	if (flag == FAILUER)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
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
