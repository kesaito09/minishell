/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd0_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 20:42:50 by natakaha          #+#    #+#             */
/*   Updated: 2026/04/29 21:58:08 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include <sys/fcntl.h>

static int		manage_redirect_module(t_token *flist, t_tree *branch,
					t_shared_info *info);
static int		redirect_in_open_dup2(t_token *flist, t_shared_info *info);
static int		redirect_out_open_dup2(t_token *flist, t_shared_info *info);

int	manage_redirect(t_tree *branch, t_shared_info *info)
{
	t_token	*file_lst;

	file_lst = branch->file_list;
	while (file_lst)
	{
		if (manage_redirect_module(file_lst, branch, info) == FAILURE)
			return (FAILURE);
		file_lst = file_lst->next;
	}
	return (SUCCESS);
}

static int	manage_redirect_module(t_token *flist, t_tree *branch,
		t_shared_info *info)
{
	if (flist->type == TOKEN_REDIRECT_OUT || flist->type == TOKEN_APPEND)
	{
		if (redirect_out_check(flist->token) == FAILURE)
			return (FAILURE);
		return (redirect_out_open_dup2(flist, info));
	}
	else
	{
		if (redirect_in_check(flist->token) == FAILURE)
			return (FAILURE);
		if (flist->type == TOKEN_REDIRECT_IN)
			return (redirect_in_open_dup2(flist, info));
		return (heredoc_open_dup2(flist, branch, info));
	}
}

static int	redirect_in_open_dup2(t_token *flist, t_shared_info *info)
{
	int	fd_in;

	fd_in = open(flist->token, O_RDONLY);
	if (fd_in < 0)
		return (err_no_such_file(info, flist->token));
	if (dup2(fd_in, 0) == FAILURE)
		return (close(fd_in), FAILURE);
	close(fd_in);
	return (SUCCESS);
}

static int	redirect_out_open_dup2(t_token *flist, t_shared_info *info)
{
	int	fd_out;

	if (flist->type == TOKEN_REDIRECT_OUT)
		fd_out = open(flist->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd_out = open(flist->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out < 0)
		return (err_no_such_file(info, flist->token));
	if (dup2(fd_out, 1) == FAILURE)
		return (close(fd_out), FAILURE);
	close(fd_out);
	return (SUCCESS);
}
