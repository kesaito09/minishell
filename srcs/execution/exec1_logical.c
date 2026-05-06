/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec1_logical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:54:42 by naoki             #+#    #+#             */
/*   Updated: 2026/05/07 07:43:56 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/main.h"

int	exec_sshell(t_tree *branch, t_shared_info *info, int fd_in, int fd_out)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), FAILURE);
	if (pid > 0)
	{
		if (pid_add_back(&(info->plist), pid) == FAILURE)
			fatal_exit(info);
		return (SUCCESS);
	}
	if (branch->file_list)
	{
		if (expander(branch->file_list, info, FILE_LIST) == FAILURE)
			child_fatal_exit(info);
		manage_redirect(branch, info);
	}
	exec_manage(branch->left, info, fd_in, fd_out);
	status = wait_pidlist(&info->plist);
	exit(status);
	return (SUCCESS);
}

int	exec_cjunc(t_tree *branch, t_shared_info *info, int fd_in, int fd_out)
{
	if (exec_manage(branch->left, info, fd_in, fd_out) == FAILURE)
		return (FAILURE);
	info->last_ecode = wait_pidlist(&info->plist);
	if (info->last_ecode != 0)
		return (FAILURE);
	if (exec_manage(branch->right, info, fd_in, fd_out) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	exec_djunc(t_tree *branch, t_shared_info *info, int fd_in, int fd_out)
{
	exec_manage(branch->left, info, fd_in, fd_out);
	info->last_ecode = wait_pidlist(&info->plist);
	if (info->last_ecode == 0)
		return (SUCCESS);
	if (exec_manage(branch->right, info, fd_in, fd_out) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	exec_pipe(t_tree *branch, t_shared_info *info, int fd_in, int fd_out)
{
	int	fd[2];

	info->pipe = true;
	if (pipe(fd) == FAILURE)
		return (perror("pipe"), FAILURE);
	info->fd[0] = fd[0];
	info->fd[1] = fd[1];
	exec_manage(branch->left, info, fd_in, fd[1]);
	close(fd[1]);
	exec_manage(branch->right, info, fd[0], fd_out);
	close(fd[0]);
	return (SUCCESS);
}
