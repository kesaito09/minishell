/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec6_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 20:42:50 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/19 06:58:49 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static int	manage_redirect_module(t_token *flist);
static int	redirect_in_open_dup2(t_token *flist);
static int	redirect_out_open_dup2(t_token *flist);

int	manage_redirect(t_token *file_lst)
{
	while (file_lst)
	{
		if (manage_redirect_module(file_lst) == FAILUER)
			return (FAILUER);
		file_lst = file_lst->next;
	}
	return (SUCCESS);
}

static int	manage_redirect_module(t_token *flist)
{
	if (flist->type == TOKEN_REDIRECT_IN
		|| flist->type == TOKEN_HEREDOC)
	{
		if (redirect_in_check(flist->token) == FAILUER
			|| redirect_in_open_dup2(flist) == FAILUER)
			return (FAILUER);
	}
	else if (flist->type == TOKEN_REDIRECT_OUT
		|| flist->type == TOKEN_APPEND)
	{
		if (redirect_out_check(flist->token) == FAILUER
			|| redirect_out_open_dup2(flist) == FAILUER)
			return (FAILUER);
	}
	return (SUCCESS);
}

static int	redirect_in_open_dup2(t_token *flist)
{
	int	fd_in;

	fd_in = open(flist->token, O_RDONLY);
	if (fd_in < 0)
		return (FAILUER);
	if (dup2(fd_in, 0) == FAILUER)
		return (FAILUER);
	if (flist->type != TOKEN_HEREDOC)
		return (SUCCESS);
	if (unlink(flist->token) == FAILUER)
		return (FAILUER);
	return (SUCCESS);
}

static int	redirect_out_open_dup2(t_token *flist)
{
	int	fd_out;

	if (flist->type == TOKEN_REDIRECT_OUT)
		fd_out = open(flist->token, O_WRONLY | O_CREAT | O_TRUNC,
				0644);
	else
		fd_out = open(flist->token, O_WRONLY | O_CREAT | O_APPEND,
				0644);
	if (fd_out < 0)
		return (FAILUER);
	if (dup2(fd_out, 1) == FAILUER)
		return (FAILUER);
	return (SUCCESS);
}
