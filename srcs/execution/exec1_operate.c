/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1_operate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:26:37 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/23 11:34:57 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	exec_manage(t_tree *branch, t_shared_info *info, int fd_in, int fd_out)
{
	if (branch->b_type == SUBSHELL)
		return (exec_sshell(branch, info, fd_in, fd_out));
	if (branch->b_type == CONJUNCTION)
		return (exec_cjunc(branch, info, fd_in, fd_out));
	if (branch->b_type == DISJUNCTION)
		return (exec_djunc(branch, info, fd_in, fd_out));
	if (branch->b_type == PIPE)
		return (exec_pipe(branch, info, fd_in, fd_out));
	if (branch->b_type == ENVP)
		return (silent_export(branch->env_list, info, TOP, 1));
	if (branch->b_type == COMMAND)
		return (exec_cmd(branch, info, fd_in, fd_out));
	if (branch->b_type == BUILTIN)
		return (exec_built(branch, info, fd_in, fd_out));
	return (SUCCESS);
}
