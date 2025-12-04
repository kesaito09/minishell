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

#include "../../includes/pipex.h"

static int	redirect_in_open_dup2(t_pipe *info, t_flist *flist)
{
	info->fd_in[0] = open(flist->file, O_RDONLY);
	if (info->fd_in[0] < 0)
		return (FAILUER);
	if (dup2(info->fd_in[0], 0) == FAILUER)
		return (FAILUER);
	return (SUCCESS);
}

static int	redirect_out_open_dup2(t_pipe *info, t_flist *flist)
{
	info->fd_out[1] = open(flist->file, O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (info->fd_out[1] < 0)
		return (FAILUER);
	if (dup2(info->fd_out[1], 1) == FAILUER)
		return (FAILUER);
	return (SUCCESS);
}

static int	append_open_dup2(t_pipe *info, t_flist *flist)
{
	info->fd_out[1] = open(flist->file, O_WRONLY | O_CREAT | O_APPEND,
			0644);
	if (info->fd_out[1] < 0)
		return (FAILUER);
	if (dup2(info->fd_out[1], 1) == FAILUER)
		return (FAILUER);
	return (SUCCESS);
}

int	manage_redirect_module(t_pipe *info, t_flist *flist)
{
	if (flist->f_type == INFILE)
	{
		if (redirect_in_open_dup2(info, flist) == FAILUER)
			return (FAILUER);
	}
	else if (flist->f_type == OUTFILE)
	{
		if (redirect_out_open_dup2(info, flist) == FAILUER)
			return (FAILUER);
	}
	else if (flist->f_type == APPEND)
	{
		if (append_open_dup2(info, flist) == FAILUER)
			return (FAILUER);
	}
	return (SUCCESS);
}

int	manage_redirect(t_pipe *info, t_tree *branch)
{
	t_flist	*cr;

	cr = branch->flist;
	while (cr)
	{
		if (manage_redirect_module(info, cr) == FAILUER)
			return (FAILUER);
		cr = cr->next;
	}
	return (SUCCESS);
}