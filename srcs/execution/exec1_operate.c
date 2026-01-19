/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1_operate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:26:37 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/19 06:07:52 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	exec_manage(t_tree *branch, t_shared_info *info, int fd_in, int fd_out)
{
	if (!branch)
		return (FAILUER);
	if (branch->b_type == SUBSHELL)
		if (exec_sshell(branch, info, fd_in, fd_out) == FAILUER)
			return (FAILUER);
	if (branch->b_type == CONJUNCTION)
		if (exec_cjunc(branch, info, fd_in, fd_out) == FAILUER)
			return (FAILUER);
	if (branch->b_type == DISJUNCTION)
		if (exec_djunc(branch, info, fd_in, fd_out) == FAILUER)
			return (FAILUER);
	if (branch->b_type == PIPE)
		if (manage_pipe(branch, info, fd_in, fd_out) == FAILUER)
			return (FAILUER);
	if (branch->b_type == ENVP)
		if (manage_envp(branch, info, fd_in, fd_out) == FAILUER)
			return (FAILUER);
	if (branch->b_type == COMMAND)
		if (exec_cmd(branch, info, fd_in, fd_out) == FAILUER)
			return (FAILUER);
	if (branch->b_type == MY_COMMAND)
		if (exec_built(branch, info, fd_in, fd_out) == FAILUER)
			return (FAILUER);
	return (SUCCESS);
}
