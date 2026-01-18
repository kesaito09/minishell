/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3_execve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:55:18 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/18 12:13:05 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_cmd.h"
#include "../../includes/execution.h"
#include <stdio.h>

static int	execve_cmd(char **envp, char **cmd);

int	manage_cmd(t_tree *branch, t_shared_info *info, int fd_in, int fd_out)
{
	pid_t	pid;
	char	**cmd;
	char	**env;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), FAILUER);
	if (pid > 0)
		return (pid_add_back(&(info->plist), pid), SUCCESS);
	setup_signal_child();
	close_unused_pipe(fd_in, fd_out, info->fd);
	if (dup2_stdin_out(fd_in, fd_out) == FAILUER)
		error_exit("dup2", 1);
	// if (manage_redirect(branch) == FAILUER
	// 	|| expander(&branch->arg_list, info, ARG_LIST) == FAILUER
	// 	|| expander(&branch->env_list, info, ENV_LIST) == FAILUER
	// 	|| expander(&branch->file_list, info, FILE_LIST) == FAILUER)
	// 	exit(1);
	// export(branch->env_list, info);
	cmd = token_argv(branch->arg_list);
	env = token_argv(info->envp);
	// if (!cmd || !env)
	// 	return (free_split(cmd), free_split(env), FAILUER);
	execve_cmd(env, cmd);
	return (FAILUER);
}

static int	execve_cmd(char **envp, char **cmd)
{
	char	*full_path;
	t_token	*path;

	if (!cmd)
		return (FAILUER);
	path = complete_path(envp);
	while (path)
	{
		full_path = ft_strjoin(path->token, cmd[0]);
		if (!full_path)
			error_exit("malloc", 1);
		execve(full_path, cmd, envp);
		free(full_path);
		path = path->next;
	}
	command_error_check(cmd[0], cmd[0]);
	execve(cmd[0], cmd, envp);
	error_exit("command not found", 127);
	return (FAILUER);
}