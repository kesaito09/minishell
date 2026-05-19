/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:55:18 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/19 17:30:30 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_cmd.h"
#include "../../includes/execution.h"
#include "../../includes/main.h"

static int	builtin_search(t_token *node, t_shared_info *info);
static int	builtin_module(t_tree *branch,
				t_shared_info *info, int fd_in, int fd_out);

int	builtin_fork(t_tree *branch, t_shared_info *info, int fd_in, int fd_out)
{
	pid_t	pid;
	int		flag;

	pid = 1;
	if (info->pipe)
		pid = fork();
	if (pid < 0)
		return (perror("fork"), FAILURE);
	if (info->pipe && pid > 0)
	{
		if (pid_add_back(&(info->plist), pid) == FAILURE)
			fatal_exit(info);
		if (env_underscore(branch->arg_list, info) == FAILURE)
			fatal_exit(info);
		return (SUCCESS);
	}
	if (info->pipe && pid == 0)
		setup_signal_child();
	flag = builtin_module(branch, info, fd_in, fd_out);
	if (pid == 0)
	{
		info->last_ecode = detect_ecode(flag, info);
		builtin_exit(NULL, info);
	}
	return (flag);
}

static int	builtin_module(t_tree *branch,
	t_shared_info *info, int fd_in, int fd_out)
{
	int	flag;

	flag = SUCCESS;
	if (info->pipe)
		manage_exporter(branch, info);
	else
		builtin_exporter(branch, info);
	if (builtin_file_descriptor(fd_in, fd_out, info, branch) == FAILURE)
		return (reset_stdin_out(info), FAILURE);
	if (builtin_search(branch->arg_list, info) == FAILURE)
		flag = FAILURE;
	if (reset_stdin_out(info) == FAILURE)
		flag = FAILURE;
	if (silent_unset(branch->env_list, info) == FAILURE)
		flag = FAILURE;
	if (env_underscore(branch->arg_list, info) == FAILURE)
		flag = FAILURE;
	return (flag);
}

static int	builtin_search(t_token *node, t_shared_info *info)
{
	if (!ft_strcmp(node->token, "echo"))
		return (echo(node->next));
	if (!ft_strcmp(node->token, "cd"))
		return (cd(node->next, info));
	if (!ft_strcmp(node->token, "pwd"))
		return (pwd(info));
	if (!ft_strcmp(node->token, "export"))
		return (export(node->next, info));
	if (!ft_strcmp(node->token, "unset"))
		return (unset(node->next, info));
	if (!ft_strcmp(node->token, "env"))
		return (env(node->next, info));
	if (!ft_strcmp(node->token, "exit"))
		builtin_exit(node->next, info);
	return (FAILURE);
}
