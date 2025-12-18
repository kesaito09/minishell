/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:36:49 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/16 21:43:53 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/readline.h"
#include "../../includes/execution.h"
#include "../../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*line;
	t_tree	*branch;
	t_pipe	info;

	info = correct_info(envp);
	while (1)
	{
		setup_signal_prompt();
		line = readline("minishell$ ");
		if (!line)
			return (rl_clear_history(), 0);
		add_history(line);
		branch = parser(line);
		setup_signal_exec();
		tree_operator(branch, &info, 0, 1);
		free_tree_rec(branch);
		info.ecode = waitpid_plist(&info.plist);
		free(line);
	}
	free_split(info.path);
	(void)argc;
	(void)argv;
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