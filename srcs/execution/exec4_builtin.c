/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec4_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:55:18 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/19 06:35:51 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_cmd.h"
#include "../../includes/execution.h"

static int	builtin_search(t_token *node, t_shared_info *info, t_tree *branch);

int	exec_built(t_tree *branch, t_shared_info *info, int fd_in, int fd_out)
{
	pid_t	pid;

	pid = 1;
	if (info->pipe)
		pid = fork();
	if (pid < 0)
		return (perror("fork"), FAILUER);
	if (info->pipe && pid > 0)
		return (pid_add_back(&(info->plist), pid), SUCCESS);
	if (info->pipe && pid == 0)
		setup_signal_child();
	close_unused_pipe(fd_in, fd_out, info->fd);
	if (dup2_stdin_out(fd_in, fd_out) == FAILUER
		|| expander(branch->arg_list, info, ARG_LIST) == FAILUER
		|| expander(branch->file_list, info, FILE_LIST) == FAILUER
		|| expander(branch->env_list, info, ENV_LIST) == FAILUER
		|| manage_redirect(branch->file_list) == FAILUER)
		return (FAILUER);
	builtin_search(branch->arg_list, info, branch);
	reset_stdin_out(info);
	if (!pid)
		exit(0);
	return (SUCCESS);
}

static int	builtin_search(t_token *node, t_shared_info *info, t_tree *branch)
{
	if (!ft_strcmp(node->token, "echo"))
		echo(node);
	if (!ft_strcmp(node->token, "cd"))
		cd(node);
	if (!ft_strcmp(node->token, "pwd"))
		pwd();
	if (!ft_strcmp(node->token, "export"))
		export(node->next, info);
	if (!ft_strcmp(node->token, "unset"))
		unset(node, info);
	if (!ft_strcmp(node->token, "env"))
		env(node, info);
	if (!ft_strcmp(node->token, "exit"))
		builtin_exit(branch, info);
	return (SUCCESS);
}
