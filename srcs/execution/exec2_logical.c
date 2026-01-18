/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2_logical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:54:42 by naoki             #+#    #+#             */
/*   Updated: 2026/01/18 09:44:51 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	manage_subshell(t_tree *branch, t_shared_info *info, int fd_in, int fd_out)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), FAILUER);
	if (pid > 0)
		return (pid_add_back(&(info->plist), pid), SUCCESS);
	tree_operator(branch->left, info, fd_in, fd_out);
	status = wait_pidlist(&info->plist);
	exit(status);
	return (SUCCESS);
}

int	manage_cjunc(t_tree *branch, t_shared_info *info, int fd_in, int fd_out)
{
	if (tree_operator(branch->left, info, fd_in, fd_out) == FAILUER)
		return (FAILUER);
	info->ecode = wait_pidlist(&info->plist);
	if (info->ecode != 0)
		return (FAILUER);
	if (tree_operator(branch->right, info, fd_in, fd_out) == FAILUER)
		return (FAILUER);
	return (SUCCESS);
}

int	manage_djunc(t_tree *branch, t_shared_info *info, int fd_in, int fd_out)
{
	if (tree_operator(branch->left, info, fd_in, fd_out) == FAILUER)
		return (FAILUER);
	info->ecode = wait_pidlist(&info->plist);
	if (info->ecode == 0)
		return (SUCCESS);
	if (tree_operator(branch->right, info, fd_in, fd_out) == FAILUER)
		return (FAILUER);
	return (SUCCESS);
}

int	manage_pipe(t_tree *branch, t_shared_info *info, int fd_in, int fd_out)
{
	int	fd[2];

	info->pipe = true;
	if (pipe(fd) == FAILUER)
		return (perror("pipe"), FAILUER);
	info->fd[0] = fd[0];
	info->fd[1] = fd[1];
	if (tree_operator(branch->left, info, fd_in, fd[1]) == FAILUER)
		return (FAILUER);
	close(fd[1]);
	if (tree_operator(branch->right, info, fd[0], fd_out) == FAILUER)
		return (FAILUER);
	return (SUCCESS);
}
