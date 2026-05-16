/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd1_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 04:00:00 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/01 00:37:28 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include <sys/fcntl.h>

static char			*redirect_heredoc(t_token *flist, int fd_in, t_tree *branch,
						t_shared_info *info);
static t_token_type	heredoc_file_type(t_token *flist, t_tree *branch);

int	heredoc_open_dup2(t_token *flist, t_tree *branch, t_shared_info *info)
{
	int		fd_raw;
	int		fd_expand;
	int		fd_dup2;
	char	*heredoc;

	fd_raw = open(flist->token, O_RDONLY);
	if (fd_raw < 0)
		return (unlink(flist->token), FAILURE);
	heredoc = redirect_heredoc(flist, fd_raw, branch, info);
	close(fd_raw);
	fd_expand = open(flist->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_expand < 0)
		return (free(heredoc), unlink(flist->token), FAILURE);
	ft_putstr_fd(heredoc, fd_expand);
	close(fd_expand);
	free(heredoc);
	fd_dup2 = open(flist->token, O_RDONLY);
	if (fd_dup2 < 0)
		return (unlink(flist->token), FAILURE);
	if (unlink(flist->token) == FAILURE)
		return (close(fd_dup2), FAILURE);
	if (dup2(fd_dup2, 0) < 0)
		return (close(fd_dup2), FAILURE);
	close(fd_dup2);
	return (SUCCESS);
}

static char	*redirect_heredoc(t_token *flist, int fd_in, t_tree *branch,
		t_shared_info *info)
{
	char	*raw_str;
	char	*expanded;

	raw_str = get_line(fd_in);
	if (!raw_str)
		fatal_exit(info);
	flist->type = heredoc_file_type(flist, branch);
	if (flist->type != SUB_TOKEN_GENERAL)
		return (raw_str);
	expanded = expand_join(raw_str, info->envp, SUB_TOKEN_DQUOTE, info);
	if (!expanded)
		fatal_exit(info);
	return (expanded);
}

static t_token_type	heredoc_file_type(t_token *flist, t_tree *branch)
{
	char	*file;
	t_token	*tmp;

	file = flist->token;
	tmp = branch->heredoc;
	while (tmp && ft_strcmp(file, tmp->token) != 0)
		tmp = tmp->next;
	return (tmp->type);
}
