/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:36:49 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/05 14:09:04 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/readline.h"

//int main(void)
//{
//	char	*line;

//	while (1)
//	{
//		line = readline("minishell$ ");
//		if (!line)
//			return (rl_clear_history(), 0);
//		add_history(line);
//		free(line);
//	}
//}

/*tester*/

//int main(int argc, char **argv, char **envp)
//{
//	t_tree	*tmp;
//	t_tree	*branch;
//	t_pipe	info;
//	char	*str;
//	char	*null;
//	char	**cmd;

//	null = (char *)NULL;

//	branch = tree_new(&null, null, PIPE);
//	info = correct_info(argc, argv, envp);

//	str = "ls -l";
//	cmd = ft_split(str, ' ');
//	tmp = tree_new(cmd, null, COMMAND);
//	tree_add_left(&branch, tmp);

//	str = "wc -l";
//	cmd = ft_split(str, ' ');
//	tmp = tree_new(cmd, null, COMMAND);
//	tree_add_right(&branch, tmp);

//	tree_operator(branch, &info, 1);
//	waitpid_plist(info.plist);
//}