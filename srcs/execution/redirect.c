/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 20:42:50 by natakaha          #+#    #+#             */
/*   Updated: 2026/04/29 21:58:08 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include <sys/fcntl.h>

static int	manage_redirect_module(t_token *flist, t_shared_info *info);
static int	redirect_in_open_dup2(t_token *flist, t_shared_info *info);
static int	redirect_out_open_dup2(t_token *flist, t_shared_info *info);
static char	*redirect_heardoc(t_token *flist, int fd, t_shared_info *info);
static int	heardoc_open_dup2(t_token *flist, t_shared_info *info);

int	manage_redirect(t_token *file_lst, t_shared_info *info)
{
	while (file_lst)
	{
		if (manage_redirect_module(file_lst, info) == FAILURE)
			return (FAILURE);
		file_lst = file_lst->next;
	}
	return (SUCCESS);
}

static int	manage_redirect_module(t_token *flist, t_shared_info *info)
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
		return (heardoc_open_dup2(flist, info));
	}
}

static int	redirect_in_open_dup2(t_token *flist, t_shared_info *info)
{
	int	fd_in;

	(void)info;
	fd_in = open(flist->token, O_RDONLY);
	if (fd_in < 0)
		return (FAILURE);
	if (dup2(fd_in, 0) == FAILURE)
		return (close(fd_in), FAILURE);
	close(fd_in);
	return (SUCCESS);
}

static char	*redirect_heardoc(t_token *flist, int fd_in, t_shared_info *info) 
{
	char	*raw_str;
	char	*expanded;
	
	raw_str = get_line(fd_in);
	if (!raw_str)
    	fatal_exit(info);
	if (flist->type != SUB_TOKEN_GENERAL)
		return (raw_str);
	expanded = expand_join(raw_str, info->envp, SUB_TOKEN_DQUOTE);
	free(raw_str);
	if (!expanded)
    	fatal_exit(info);
	return (expanded);
}

static int	heardoc_open_dup2(t_token *flist, t_shared_info *info)
{
	int		fd_raw;
	int		fd_expand;
	int		fd_dup2;
	char	*heardoc;

	fd_raw = open(flist->token, O_RDONLY);
	if (fd_raw < 0)
		return (FAILURE);
	heardoc = redirect_heardoc(flist, fd_raw, info);
	close(fd_raw);
	fd_expand = open(flist->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_expand < 0)
		return (free(heardoc), FAILURE);
	ft_putstr_fd(heardoc, fd_expand);
	close(fd_expand);
	free(heardoc);
	fd_dup2 = open(flist->token, O_RDONLY);
	if (fd_dup2 < 0)
		return (FAILURE);
	if (unlink(flist->token) == FAILURE)
		return (FAILURE);
	return (dup2(fd_dup2, 0));
}

static int	redirect_out_open_dup2(t_token *flist, t_shared_info *info)
{
	int	fd_out;

	(void)info;
	if (flist->type == TOKEN_REDIRECT_OUT)
		fd_out = open(flist->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd_out = open(flist->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out < 0)
		return (FAILURE);
	if (dup2(fd_out, 1) == FAILURE)
		return (close(fd_out), FAILURE);
	close(fd_out);
	return (SUCCESS);
}
