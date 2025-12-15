/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:55:18 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/10 02:43:34 by natakaha         ###   ########.fr       */
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
			return (FAILUER);
		execve(full_path, cmd, envp);
		free(full_path);
		i++;
	}
	command_error_check(cmd[0], cmd[0]);
	execve(cmd[0], cmd, envp);
	return (FAILUER);
}

static int	execve_my_cmd(char **cmd, t_pipe *info)
{
	if (!ft_strcmp(cmd[0], "echo"))
		echo(cmd);
	if (!ft_strcmp(cmd[0], "cd"))
		cd(cmd);
	if (!ft_strcmp(cmd[0], "pwd"))
		pwd(cmd);
	if (!ft_strcmp(cmd[0], "export"))
		export(cmd, info);
	if (!ft_strcmp(cmd[0], "unset"))
		echo(cmd);
	if (!ft_strcmp(cmd[0], "env"))
		env(cmd, info);
	if (!ft_strcmp(cmd[0], "exit"))
		echo(cmd);
	return (SUCCESS);
}

int	manage_cmd(t_tree *branch, t_pipe *info, int fd_in, int fd_out)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		error_exit("fork:", 1);
	if (pid == 0)
	{
		close_unused_pipe(fd_in, fd_out, info->fd);
		if (dup2_stdin_out(fd_in, fd_out) == FAILUER)
			error_exit("dup2:", 1);
		if (manage_redirect(branch) == FAILUER)
			return (FAILUER);
		if (execve_cmd(info->path, info->envp, branch->argv) == FAILUER)
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
	close_unused_pipe(fd_in, fd_out, info->fd);
	if (dup2_stdin_out(fd_in, fd_out) == FAILUER 
		|| manage_redirect(branch) == FAILUER)
		return (FAILUER);
	execve_my_cmd(branch->argv, info);
	reset_stdin_out(info);
	if (!pid)
		exit(0);
	return (SUCCESS);
}
