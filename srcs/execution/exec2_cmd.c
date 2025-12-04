/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:55:18 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/02 06:55:21 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.h"
#include "../../includes/pipex.h"

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
			return (error_exit(cmd, "malloc failed", 1), 1);
		execve(full_path, cmd, envp);
		free(full_path);
		i++;
	}
	return (error_exit(cmd, "execve failed", 127), FAILUER);
}

static int	execve_my_cmd(char **cmd)
{
	if (!ft_strcmp(cmd[0], "echo"))
		echo(cmd);
	if (!ft_strcmp(cmd[0], "cd"))
		cd(cmd);
	if (!ft_strcmp(cmd[0], "pwd"))
		pwd(cmd);
	if (!ft_strcmp(cmd[0], "export"))
		echo(cmd);
	if (!ft_strcmp(cmd[0], "unset"))
		echo(cmd);
	if (!ft_strcmp(cmd[0], "env"))
		echo(cmd);
	if (!ft_strcmp(cmd[0], "exit"))
		echo(cmd);
	return (SUCCESS);
}

void	manage_cmd(t_tree *branch, t_pipe *info, pid_t pid)
{
	if (pid > 0)
		pid = fork();
	if (pid < 0)
		return (free_path(branch->argv));
	if (pid > 0)
		return (pid_add_back(&(info->plist), pid));
	if (pid == 0)
	{
		if (dup2_stdin_out(info->fd_in[0], info->fd_out[1]) == FAILUER)
				error_exit(branch->argv, "", 1);
		if (manage_redirect(info, branch) == FAILUER)
			error_exit(branch->argv, "", 1);
		execve_cmd(info->path, info->envp, branch->argv);
		reset_stdin_out(info);
		error_exit(branch->argv, "", 1);
	}
}

void	manage_my_cmd(t_tree *branch, t_pipe *info, pid_t pid)
{
	if (manage_redirect(info, branch) == FAILUER)
		exit(1);
	execve_my_cmd(branch->argv);
	reset_stdin_out(info);
	free_path(branch->argv);
	(void)pid;
}
