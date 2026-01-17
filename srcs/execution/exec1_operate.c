/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1_operate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:26:37 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/17 16:59:31 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	tree_operator(t_tree *branch, t_shared_info *info, int fd_in, int fd_out)
{
	if (!branch)
		return (FAILUER);
	if (branch->b_type == SUBSHELL)
		if (manage_subshell(branch, info, fd_in, fd_out) == FAILUER)
			return (FAILUER);
	if (branch->b_type == CONJUNCTION)
		if (manage_conjunction(branch, info, fd_in, fd_out) == FAILUER)
			return (FAILUER);
	if (branch->b_type == DISJUNCTION)
		if (manage_disjunction(branch, info, fd_in, fd_out) == FAILUER)
			return (FAILUER);
	if (branch->b_type == PIPE)
		if (manage_pipe(branch, info, fd_in, fd_out) == FAILUER)
			return (FAILUER);
	if (branch->b_type == ENVP)
		if (manage_envp(branch, info, fd_in, fd_out) == FAILUER)
			return (FAILUER);
	if (branch->b_type == COMMAND)
		if (manage_cmd(branch, info, fd_in, fd_out) == FAILUER)
			return (FAILUER);
	if (branch->b_type == MY_COMMAND)
		if (manage_my_cmd(branch, info, fd_in, fd_out) == FAILUER)
			return (FAILUER);
	return (SUCCESS);
}
