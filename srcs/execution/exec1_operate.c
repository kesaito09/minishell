/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1_operate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:26:37 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/10 01:23:22 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	tree_operator(t_tree *branch, t_pipe *info, int fd_in, int fd_out)
{
	if (!branch)
		return  (FAILUER);
	if (branch->b_type == PIPE)
		if (manage_pipe(branch, info, fd_in, fd_out) == FAILUER)
			return (FAILUER);
	if (branch->b_type == COMMAND)
		if (manage_cmd(branch, info, fd_in, fd_out) == FAILUER)
			return (FAILUER);
	if (branch->b_type == MY_COMMAND)
		if (manage_my_cmd(branch, info, fd_in, fd_out) == FAILUER)
			return (FAILUER);
	return (SUCCESS);
}
