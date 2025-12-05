/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:54:42 by naoki             #+#    #+#             */
/*   Updated: 2025/12/05 13:27:34 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

static int	treat_pipe_left(t_tree *branch, t_pipe *info, pid_t pid)
{
	if (pipe_update(info->fd_in, info->fd_out) == FAILUER)
		return (FAILUER);
	pid = fork();
	if (pid < 0)
		return (FAILUER);
	if (pid > 0)
		pid_add_back(&(info->plist), pid);
	if (pid == 0)
	{
		close(info->fd_out[0]);
		tree_operator(branch->left, info, pid);
	}
	return (SUCCESS);
}

static int	treat_pipe_right(t_tree *branch, t_pipe *info, pid_t pid)
{
	if (branch->right->b_type == PIPE)
		tree_operator(branch->right, info, pid);
	if (pipe_terminate(info->fd_in, info->fd_out) == FAILUER)
		return (FAILUER);
	pid = fork();
	if (pid < 0)
		return (FAILUER);
	if (pid > 0)
	{
		close_fd_in_out(&(info->fd_in[0]), &(info->fd_in)[1]);
		close_fd_in_out(&(info->fd_out[0]), &(info->fd_out)[1]);
		pid_add_back(&(info->plist), pid);
	}
	if (pid == 0)
	{
		close(info->fd_in[1]);
		tree_operator(branch->right, info, pid);
	}
	return (SUCCESS);
}

void	manage_pipe(t_tree *branch, t_pipe *info, pid_t pid)
{
	if (pid == 0)
		exit(0);
	if (treat_pipe_left(branch, info, pid) == FAILUER)
		exit(1);
	if (treat_pipe_right(branch, info, pid) == FAILUER)
		exit(1);
	return ;
}
