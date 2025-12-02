/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 20:42:50 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/02 12:38:25 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	redirect_in_open_dup2(t_pipe *info, t_tree *branch)
{
	if (!branch->redirect_in)
		return (SUCCESS);
	info->fd_in[0] = open(branch->redirect_in, O_RDONLY);
	if (info->fd_in[0] < 0)
		return (FAIL);
	if (dup2(info->fd_in[0], 0) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

static int	redirect_out_open_dup2(t_pipe *info, t_tree *branch)
{

	if (!branch->redirect_out)
		return (SUCCESS);
	info->fd_out[1] = open(branch->redirect_out, O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (info->fd_out[1] < 0)
		return (FAIL);
	if (dup2(info->fd_out[1], 1) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

static int	append_open_dup2(t_pipe *info, t_tree *branch)
{
	if (!branch->append)
		return (SUCCESS);
	info->fd_out[1] = open(branch->append, O_WRONLY | O_CREAT | O_APPEND,
			0644);
	if (info->fd_out[1] < 0)
		return (FAIL);
	if (dup2(info->fd_out[1], 1) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	manage_redirect(t_pipe *info, t_tree *branch)
{
	if (redirect_in_open_dup2(info, branch) == FAIL)
		return (FAIL);
	if (redirect_out_open_dup2(info, branch) == FAIL)
		return (FAIL);
	if (append_open_dup2(info, branch) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	manage_fd(t_pipe *info)
{
	if (info->fd_in[0] != -1 && info->fd_in[1] != -1)
	{
		close(info->fd_in[0]);
		close(info->fd_in[1]);
	}
	else if (pipe(info->fd_out) == FAIL)
		return (FAIL);
	info->fd_in[0] = info->fd_out[0];
	info->fd_in[1] = info->fd_out[1];
	if (pipe(info->fd_out) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	fd_stdout(t_pipe *info)
{
	if (info->fd_in[0] != -1 && info->fd_in[1] != -1)
	{
		close(info->fd_in[0]);
		close(info->fd_in[1]);
	}
	info->fd_in[0] = info->fd_out[0];
	return (SUCCESS);
}
