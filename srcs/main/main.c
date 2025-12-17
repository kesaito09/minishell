/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:36:49 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/17 12:59:13 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../includes/readline.h"
#include "../../includes/execution.h"
#include "../../includes/minishell.h"

// int	main_stream(char *line)
// {
// 	parser(line);






// }




// int main(int argc, char **argv, char **envp)
// {
// 	char	*line;
// 	t_tree	*branch;
// 	t_pipe	info;

// 	info = correct_info(envp);
// 	while (1)
// 	{
// 		line = readline("minishell$ ");
// 		if (!line)
// 			return (rl_clear_history(), 0);
// 		add_history(line);
// 		branch = parser(line);
// 		tree_operator(branch, &info, 0, 1);
// 		waitpid_plist(info.plist);
// 		free(line);
// 	}
// 	(void)argc;
// 	(void)argv;
// }

// /*tester*/

int main(int argc, char **argv, char **envp)
{
	t_tree	*branch;
	t_pipe	info;

	if (argc < 2)
		return (0);
	info = correct_info(envp);
	branch = parser(argv[1]);
	tree_operator(branch, &info, 0, 1);
	free_tree_rec(branch);
	free_split(info.path);
	waitpid_plist(info.plist);
	free_pid(info.plist);
}
