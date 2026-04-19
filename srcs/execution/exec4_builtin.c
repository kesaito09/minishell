/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec4_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:55:18 by natakaha          #+#    #+#             */
/*   Updated: 2026/04/19 19:18:46 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_cmd.h"
#include "../../includes/execution.h"

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
		return (perror("fork"), FAILUER);
	if (info->pipe && pid > 0)
	{
		if (pid_add_back(&(info->plist), pid) == SUCCESS
		&& env_underscore(branch->arg_list, info) == SUCCESS)
			return (SUCCESS);
		return (FAILUER);
	}
	if (info->pipe && pid == 0)
		setup_signal_child();
	flag = builtin_module(branch, info, fd_in, fd_out);
	if (pid == 0 && flag == FAILUER)
		exit(EXIT_FAILURE);
	else if (pid == 0)
		exit(EXIT_SUCCESS);
	return (flag);
}

static int	builtin_module(t_tree *branch,
	t_shared_info *info, int fd_in, int fd_out)
{
	int	flag;
	
	flag = SUCCESS;
	manage_expander(branch, info);
	manage_exporter(branch, info);
	if (builtin_file_descriptor(fd_in, fd_out, info, branch) == FAILUER)
		flag = FAILUER;
	if (builtin_search(branch->arg_list, info) == FAILUER)
		flag = FAILUER;
	if (reset_stdin_out(info) == FAILUER)
		flag = FAILUER;
	if (silent_unset(branch->env_list, info) == FAILUER)
		flag = FAILUER;
	if (env_underscore(branch->arg_list, info) == FAILUER)
	{
		info->last_ecode = 2;
		builtin_exit(NULL, info);
	}
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
	return (FAILUER);
}
