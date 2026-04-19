/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6_exec_module.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 19:14:31 by naoki             #+#    #+#             */
/*   Updated: 2026/04/18 21:40:06 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	manage_file_descriptor(int fd_in, int fd_out ,t_shared_info *info, t_tree *branch)
{
	close_unused_pipe(fd_in, fd_out, info->fd);
	if (dup2_stdin_out(fd_in, fd_out) == FAILUER
	|| manage_redirect(branch->file_list) == FAILUER)
	{	
		info->last_ecode = 1;
		builtin_exit(NULL, info);
	}
	return (SUCCESS);
}

int	manage_expander(t_tree *branch, t_shared_info *info)
{
	if (expander(branch->arg_list, info, ARG_LIST) == FAILUER
		|| expander(branch->env_list, info, ENV_LIST) == FAILUER
		|| expander(branch->file_list, info, FILE_LIST) == FAILUER)
	{
		info->last_ecode = 1;
		builtin_exit(NULL, info);
	}
	return (SUCCESS);	
}

int	manage_exporter(t_tree *branch, t_shared_info *info)
{
	if (silent_export(branch->env_list, info, TOP, 0) == FAILUER
	|| env_underscore(branch->arg_list, info) == FAILUER)
	{
		info->last_ecode = 2;
		builtin_exit(NULL, info);
	}	
	return (SUCCESS);
}

char	**manage_arg_load(t_shared_info *info, t_token *node)
{
	char	**argv;

	if (!node)
		return (NULL);
	argv = token_argv(node);
	if (!argv)
	{
		info->last_ecode = 2;
		builtin_exit(NULL, info);		
	}
	return (argv);
}
