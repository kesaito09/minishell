/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:36:49 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/01 20:50:21 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/readline.h"
#include "../../includes/execution.h"
#include "../../includes/minishell.h"

char	*get_line(int fd)
{
	char	*tmp;
	char	*trash;
	char	*line;

	tmp = "tmp";
	line = NULL;
	while (tmp)
	{
		trash = line;
		tmp = get_next_line(fd);
		line = ft_strjoin(line, tmp);
		free(tmp);
		free(trash);
		if (!line)
			return (NULL);
	}
	return (line);
}

int	minishell_atty(t_pipe *info)
{
	char	*line;
	t_tree	*branch;
	int		flag;

	flag = SUCCESS;
	while (true)
	{
		setup_signal_prompt();
		line = readline("minishell$ ");
		if (!line)
			return (rl_clear_history(), SUCCESS);
		if (!*line)
			continue ;
		add_history(line);
		branch = parser(line, info);
		free(line);
		if (!branch)
			return (rl_clear_history(), FAILUER);
		setup_signal_exec();
		flag = tree_operator(branch, info, 0, 1);
		free_tree_rec(branch);
		info->ecode = waitpid_plist(&info->plist);
		info->pipe = false;
	}
	return (flag);
}

int	minishell_pipe(t_pipe *info)
{
	char	*line;
	t_tree	*branch;
	int		flag;

	line = get_line(STDIN_FILENO);
	if (!line)
		return (FAILUER);
	branch = parser(line, info);
	if (!branch)
		return (free(line), FAILUER);
	flag = tree_operator(branch, info, 0, 1);
	free_tree_rec(branch);
	info->ecode = waitpid_plist(&info->plist);
	free(line);
	return (flag);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	info;
	int		flag;

	info = collect_info(envp);
	if (!isatty(STDIN_FILENO))
		flag = minishell_pipe(&info);
	else
		flag = minishell_atty(&info);
	free_split(info.path);
	t_lstclear(&info.envp, free);
	(void)argc;
	(void)argv;
	if (flag == FAILUER)
		return (1);
	return (0);
}

// /*tester*/

//int main(int argc, char **argv, char **envp)
//{
//	t_tree	*branch;
//	t_pipe	info;

//	if (argc < 2)
//		return (0);
//	info = correct_info(envp);
//	branch = parser(argv[1]);
//	tree_operator(branch, &info, 0, 1);
//	free_tree_rec(branch);
//	free_split(info.path);
//	waitpid_plist(info.plist);
//	free_pid(info.plist);
//}

//int	main(void)
//{
//	while(1);
//}
