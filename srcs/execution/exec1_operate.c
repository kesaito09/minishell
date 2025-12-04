/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_operate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:26:37 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/02 12:32:59 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	tree_operator(t_tree *branch, t_pipe *info, pid_t pid)
{
	if (branch->b_type == PIPE)
		manage_pipe(branch, info, pid);
	if (branch->b_type == COMMAND)
		manage_cmd(branch, info, pid);
	if (branch->b_type == MY_COMMAND)
		manage_my_cmd(branch, info, pid);
	else
		return ;
}
