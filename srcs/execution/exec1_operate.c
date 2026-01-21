/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1_operate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:26:37 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/21 18:17:08 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	exec_manage(t_tree *branch, t_shared_info *info, int fd_in, int fd_out)
{
	if (!branch)
		return (FAILUER);
	if (branch->b_type == SUBSHELL)
		return (exec_sshell(branch, info, fd_in, fd_out));
	if (branch->b_type == CONJUNCTION)
		return (exec_cjunc(branch, info, fd_in, fd_out));
	if (branch->b_type == DISJUNCTION)
		return (exec_djunc(branch, info, fd_in, fd_out));
	if (branch->b_type == PIPE)
		return (manage_pipe(branch, info, fd_in, fd_out));
	if (branch->b_type == ENVP)
		return (manage_envp(branch, info, fd_in, fd_out));
	if (branch->b_type == COMMAND)
		if (exec_cmd(branch, info, fd_in, fd_out) == FAILUER
			|| env_underscore(branch->arg_list, info) == FAILUER)
			return (FAILUER);
	if (branch->b_type == MY_COMMAND)
		if (exec_built(branch, info, fd_in, fd_out) == FAILUER
			|| env_underscore(branch->arg_list, info) == FAILUER)
			return (FAILUER);
	return (SUCCESS);
}
