/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:54:42 by naoki             #+#    #+#             */
/*   Updated: 2025/12/16 14:00:40 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	manage_conjunction(t_tree *branch, t_pipe *info, int fd_in, int fd_out)
{
	if (tree_operator(branch->left, info, fd_in, fd_out) == FAILUER)
		return (FAILUER);
	info->ecode = waitpid_plist(&info->plist);
	if (info->ecode != 0)
		return (FAILUER);
	if (tree_operator(branch->right, info, fd_in, fd_out) == FAILUER)
		return (FAILUER);
	return (SUCCESS);
}

int	manage_disjunction(t_tree *branch, t_pipe *info, int fd_in, int fd_out)
{
	if (tree_operator(branch->left, info, fd_in, fd_out) == FAILUER)
		return (FAILUER);
	info->ecode = waitpid_plist(&info->plist);
	if (info->ecode == 0)
		return (SUCCESS);
	if (tree_operator(branch->right, info, fd_in, fd_out) == FAILUER)
		return (FAILUER);
	return (SUCCESS);
}

int	manage_pipe(t_tree *branch, t_pipe *info, int fd_in, int fd_out)
{
	int	fd[2];

	info->pipe = true;
	if (pipe(fd) == FAILUER)
		return (perror("minishell:pipe"), FAILUER);
	info->fd[0] = fd[0];
	info->fd[1] = fd[1];
	if (tree_operator(branch->left, info, fd_in, fd[1]) == FAILUER)
		return (FAILUER);
	close(fd[1]);
	if (tree_operator(branch->right, info, fd[0], fd_out) == FAILUER)
		return (FAILUER);
	return (SUCCESS);
}
