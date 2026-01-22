/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec4_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:55:18 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/23 00:38:24 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_cmd.h"
#include "../../includes/execution.h"

static int	builtin_search(t_token *node, t_shared_info *info);
static int	exec_builtin_module(t_tree *branch,
				t_shared_info *info, int fd_in, int fd_out);

int	exec_built(t_tree *branch, t_shared_info *info, int fd_in, int fd_out)
{
	pid_t	pid;
	int		flag;

	pid = 1;
	if (info->pipe)
		pid = fork();
	if (pid < 0)
		return (perror("fork"), FAILUER);
	if (info->pipe && pid > 0)
		return (pid_add_back(&(info->plist), pid),
			env_underscore(branch->arg_list, info), SUCCESS);
	if (info->pipe && pid == 0)
		setup_signal_child();
	flag = exec_builtin_module(branch, info, fd_in, fd_out);
	if (!pid)
		exit(flag);
	g_exit_code = flag;
	return (SUCCESS);
}

static int	exec_builtin_module(t_tree *branch,
	t_shared_info *info, int fd_in, int fd_out)
{
	close_unused_pipe(fd_in, fd_out, info->fd);
	if (dup2_stdin_out(fd_in, fd_out) == FAILUER
		|| expander(branch->arg_list, info, ARG_LIST) == FAILUER
		|| expander(branch->file_list, info, FILE_LIST) == FAILUER
		|| expander(branch->env_list, info, ENV_LIST) == FAILUER
		|| manage_redirect(branch->file_list) == FAILUER
		|| silent_export(branch->env_list, info, TOP, 0) == FAILUER
		|| builtin_search(branch->arg_list, info) == FAILUER
		|| reset_stdin_out(info) == FAILUER
		|| env_underscore(branch->arg_list, info) == FAILUER)
		return (FAILUER);
	return (SUCCESS);
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
		builtin_exit(info);
	return (FAILUER);
}
