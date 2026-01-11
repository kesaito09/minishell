/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:55:18 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/11 18:21:29 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.h"
#include "../../includes/execution.h"

static int	execve_cmd(char **path, char **envp, char **cmd)
{
	int		i;
	char	*full_path;

	i = 0;
	if (!cmd)
		return (FAILUER);
	while (path[i])
	{
		full_path = ft_strjoin(path[i], cmd[0]);
		if (!full_path)
			error_exit("malloc", 1);
		execve(full_path, cmd, envp);
		free(full_path);
		i++;
	}
	command_error_check(cmd[0], cmd[0]);
	execve(cmd[0], cmd, envp);
	error_exit("command not found", 127);
	return (FAILUER);
}

static int	execve_my_cmd(t_token *node, t_pipe *info, t_tree *branch)
{
	if (!ft_strcmp(node->token, "echo"))
		echo(node);
	if (!ft_strcmp(node->token, "cd"))
		cd(node);
	if (!ft_strcmp(node->token, "pwd"))
		pwd();
	if (!ft_strcmp(node->token, "export"))
		export(node, info);
	if (!ft_strcmp(node->token, "unset"))
		unset(node, info);
	if (!ft_strcmp(node->token, "env"))
		env(node, info);
	if (!ft_strcmp(node->token, "exit"))
		builtin_exit(branch, info);
	return (SUCCESS);
}

int	manage_cmd(t_tree *branch, t_pipe *info, int fd_in, int fd_out)
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
	if (manage_redirect(branch) == FAILUER
		|| expander(&branch->arg_list, info->envp, ARG_LIST) == FAILUER
		|| expander(&branch->file_list, info->envp, FILE_LIST) == FAILUER)
		exit(1);
	t_lstadd_back(&info->envp, branch->env_list);
	cmd = token_argv(branch->arg_list);
	env = token_argv(info->envp);
	if (!cmd || !env)
		return (free_split(cmd), free_split(env), FAILUER);
	execve_cmd(info->path, env, cmd);
	exit(127);
}

int	manage_envp(t_tree *branch, t_pipe *info, int fd_in, int fd_out)
{
	t_token	*env;

	env = branch->env_list;
	if (branch->arg_list)
		manage_cmd(branch, info, fd_in, fd_out);
	else
		if (local_env(env, info) == FAILUER)
			return (FAILUER);
	return (SUCCESS);
}

int	manage_my_cmd(t_tree *branch, t_pipe *info, int fd_in, int fd_out)
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
		|| manage_redirect(branch) == FAILUER
		|| expander(&branch->arg_list, info->envp, ARG_LIST) == FAILUER
		|| expander(&branch->file_list, info->envp, FILE_LIST) == FAILUER)
		return (FAILUER);
	execve_my_cmd(branch->arg_list, info, branch);
	reset_stdin_out(info);
	if (!pid)
		exit(0);
	return (SUCCESS);
}
