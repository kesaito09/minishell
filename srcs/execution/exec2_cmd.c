/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:55:18 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/20 05:00:11 by natakaha         ###   ########.fr       */
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
			error_exit("minishell: malloc", 1);
		execve(full_path, cmd, envp);
		free(full_path);
		i++;
	}
	command_error_check(cmd[0], cmd[0]);
	execve(cmd[0], cmd, envp);
	return (FAILUER);
}

static int	execve_my_cmd(t_token *node, t_pipe *info)
{
	if (!ft_strcmp(node->token, "echo"))
		echo(node);
	if (!ft_strcmp(node->token, "cd"))
		cd(node);
	if (!ft_strcmp(node->token, "pwd"))
		pwd(node);
	if (!ft_strcmp(node->token, "export"))
		export(node, info);
	if (!ft_strcmp(node->token, "unset"))
		unset(node, info);
	if (!ft_strcmp(node->token, "env"))
		env(node, info);
	if (!ft_strcmp(node->token, "exit"))
		echo(node);
	return (SUCCESS);
}

int	manage_cmd(t_tree *branch, t_pipe *info, int fd_in, int fd_out)
{
	pid_t	pid;
	char	**cmd;
	char	**env;

	pid = fork();
	if (pid < 0)
		return (perror("minishell: fork"), FAILUER);
	if (pid == 0)
	{
		setup_signal_child();
		close_unused_pipe(fd_in, fd_out, info->fd);
		if (dup2_stdin_out(fd_in, fd_out) == FAILUER)
			error_exit("minishell: dup2", 1);
		if (manage_redirect(branch) == FAILUER)
			exit(1);
		cmd = token_argv(branch->arg_list);
		env = token_argv(info->envp);
		if (!cmd || !env)
			return (FAILUER);
		if (execve_cmd(info->path, info->envp, cmd) == FAILUER)
			error_exit("command not found", 127);
	}
	return (pid_add_back(&(info->plist), pid), SUCCESS);
}

int	manage_my_cmd(t_tree *branch, t_pipe *info, int fd_in, int fd_out)
{
	pid_t	pid;

	pid = 1;
	if (info->pipe)
		pid = fork();
	if (pid < 0)
		return (FAILUER);
	if (info->pipe && pid > 0)
		return (pid_add_back(&(info->plist), pid), SUCCESS);
	if (info->pipe && pid == 0)
		setup_signal_child();
	close_unused_pipe(fd_in, fd_out, info->fd);
	if (dup2_stdin_out(fd_in, fd_out) == FAILUER
		|| manage_redirect(branch) == FAILUER)
		return (FAILUER);
	execve_my_cmd(branch->arg_list, info);
	reset_stdin_out(info);
	if (!pid)
		exit(0);
	return (SUCCESS);
}
