/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 08:08:01 by natakaha          #+#    #+#             */
/*   Updated: 2026/04/19 22:00:00 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_cmd.h"
#include "../../includes/execution.h"
#include "../../includes/main.h"

static void	not_numeric(char *input);
static void	close_saved_fds(t_shared_info *info);

void	builtin_exit(t_token *node, t_shared_info *info)
{
	int	num;

	if (!node)
		num = info->last_ecode;
	else if (node->next)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return ;
	}
	else if (!ft_isnumber(node->token))
	{
		not_numeric(node->token);
		num = 255;
	}
	else
		num = ft_atoi(node->token) % 256;
	free_tree_rec(&info->branch);
	wait_pidlist(&info->plist);
	t_lstclear(&info->input, free);
	t_lstclear(&info->envp, free);
	close_saved_fds(info);
	clear_history();
	exit(num);
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

static void	not_numeric(char *input)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(input, 2);
	ft_putendl_fd(": numeric argument required", 2);
	return ;
}
