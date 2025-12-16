/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec4_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 20:42:50 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/10 01:32:43 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static int	redirect_in_open_dup2(t_flist *flist)
{
	int	fd_in;

	fd_in = open(flist->file, O_RDONLY);
	if (fd_in < 0)
		return (FAILUER);
	if (dup2(fd_in, 0) == FAILUER)
		return (FAILUER);
	return (SUCCESS);
}

static int	redirect_out_open_dup2(t_flist *flist)
{
	int	fd_out;

	fd_out = open(flist->file, O_WRONLY | O_CREAT | O_TRUNC,
			0644);
	if (fd_out < 0)
		return (FAILUER);
	if (dup2(fd_out, 1) == FAILUER)
		return (FAILUER);
	return (SUCCESS);
}

static int	append_open_dup2(t_flist *flist)
{
	int	fd_out;

	fd_out = open(flist->file, O_WRONLY | O_CREAT | O_APPEND,
			0644);
	if (fd_out < 0)
		return (FAILUER);
	if (dup2(fd_out, 1) == FAILUER)
		return (FAILUER);
	return (SUCCESS);
}

static int	manage_redirect_module(t_flist *flist)
{
	if (flist->f_type == INFILE)
	{
		if (redirect_in_check(flist->file) == FAILUER
			|| redirect_in_open_dup2(flist) == FAILUER)
			return (FAILUER);
	}
	else if (flist->f_type == OUTFILE)
	{
		if (redirect_out_check(flist->file) == FAILUER
			|| redirect_out_open_dup2(flist) == FAILUER)
			return (FAILUER);
	}
	else if (flist->f_type == APPEND)
	{
		if (redirect_out_check(flist->file) == FAILUER
			|| append_open_dup2(flist) == FAILUER)
			return (FAILUER);
	}
	return (SUCCESS);
}

int	manage_redirect(t_tree *branch)
{
	t_flist	*cr;

	cr = branch->flist;
	while (cr)
	{
		if (manage_redirect_module(cr) == FAILUER)
			return (FAILUER);
		cr = cr->next;
	}
	return (SUCCESS);
}