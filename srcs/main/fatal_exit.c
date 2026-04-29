/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatal_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 22:00:00 by natakaha          #+#    #+#             */
/*   Updated: 2026/04/19 22:00:00 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/main.h"
#include "../../includes/minishell.h"
#include "../../includes/parser.h"

static void	close_saved_fds(t_shared_info *info);

void	fatal_exit(t_shared_info *info)
{
	if (info)
	{
		heardoc_clear(&info->heardoc);
		t_lstclear(&info->input, free);
		free_tree_rec(&info->branch);
		wait_pidlist(&info->plist);
		t_lstclear(&info->envp, free);
		close_saved_fds(info);
	}
	clear_history();
	ft_putendl_fd("minishell: fatal error", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	child_fatal_exit(t_shared_info *info)
{
	if (info)
	{
		heardoc_clear(&info->heardoc);
		t_lstclear(&info->input, free);
		free_tree_rec(&info->branch);
		t_lstclear(&info->envp, free);
		close_saved_fds(info);
	}
	ft_putendl_fd("minishell: fatal error", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

static void	close_saved_fds(t_shared_info *info)
{
	if (info->fd[0] >= 0)
		close(info->fd[0]);
	if (info->fd[1] >= 0)
		close(info->fd[1]);
	if (info->fd_stdin > STDERR_FILENO)
		close(info->fd_stdin);
	if (info->fd_stdout > STDERR_FILENO)
		close(info->fd_stdout);
}
