/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:14:31 by naoki             #+#    #+#             */
/*   Updated: 2026/04/29 21:58:08 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/main.h"

int	builtin_file_descriptor(int fd_in, int fd_out, t_shared_info *info,
		t_tree *branch)
{
	close_unused_pipe(fd_in, fd_out, info->fd);
	if (dup2_stdin_out(fd_in, fd_out) == FAILURE
		|| manage_redirect(branch, info) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	builtin_expander(t_tree *branch, t_shared_info *info)
{
	if (expander(branch->arg_list, info, ARG_LIST) == FAILURE
		|| expander(branch->env_list, info, ENV_LIST) == FAILURE
		|| expander(branch->file_list, info, FILE_LIST) == FAILURE)
		fatal_exit(info);
	return (SUCCESS);
}

int	builtin_exporter(t_tree *branch, t_shared_info *info)
{
	if (silent_export(branch->env_list, info, TOP, 0) == FAILURE
		|| env_underscore(branch->arg_list, info) == FAILURE)
		fatal_exit(info);
	return (SUCCESS);
}

char	**builtin_arg_load(t_shared_info *info, t_token *node)
{
	char	**argv;

	if (!node)
		return (NULL);
	argv = token_argv(node);
	if (!argv)
		fatal_exit(info);
	return (argv);
}
