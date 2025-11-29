/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:26:37 by natakaha          #+#    #+#             */
/*   Updated: 2025/11/29 16:00:25 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
#include "../includes/commands.h"

static int	execve_cmds(char **path, char **envp, char **cmd)
{
	int		i;
	char	*full_path;

	i = 0;
	if (!cmd)
		return (FAIL);
	while (path[i])
	{
		full_path = ft_strjoin(path[i], cmd[0]);
		if (!full_path)
			return (error_exit(cmd, "malloc failed", 1), 1);
		execve(full_path, cmd, envp);
		free(full_path);
		i++;
	}
	return (error_exit(cmd, "execve failed", 127), FAIL);
}
static int	execve_my_cmds(char **cmd, pid_t pid)
{
	if (!ft_strcmp(cmd[0], "echo" && !pid))
		echo(cmd);
	if (!ft_strcmp(cmd[0], "cd" && pid))
		cd(cmd);
	if (!ft_strcmp(cmd[0], "pwd" && !pid))
		pwd(cmd);
	if (!ft_strcmp(cmd[0], "export" && pid))
		echo(cmd);
	if (!ft_strcmp(cmd[0], "unset" && pid))
		echo(cmd);
	if (!ft_strcmp(cmd[0], "env" && !pid))
		echo(cmd);
	if (!ft_strcmp(cmd[0], "exit" && !pid))
		echo(cmd);
	if (!pid)
		exit(0);
	if (pid)
		return (SUCCESS);
}

void	pipe_operator(t_tree *branch, t_pipe info, pid_t pid)
{
	if (branch->mode == 'c' && !pid)
		execve_cmds(info.path, info.envp, branch->argv);
	else if (branch->mode == 'x')
		execve_my_cmds(branch->argv, pid);
	else if (branch->mode == 'p' && pid)
		
}



//int	cmd_operate(t_pipe info, int i)
//{
//	int	rf;
//	int	wf;

//	if (i == FIRST)
//	{
//		rf = open(info.argv[1], O_RDWR);
//		if (rf < 0)
//			error_exit(info.path, info.argv[1], 1);
//		dup2_or_exit(info, rf, 0);
//	}
//	if (i == info.LAST)
//	{
//		wf = open(info.argv[info.argc -1], O_RDWR);
//		if (wf < 0)
//			error_exit(info.path, info.argv[info.argc - 1], 1);
//		dup2_or_exit(info, wf, 1);
//	}
//	execve_cmds(info.path, info.envp, info.argv[i]);
//	error_exit(info.path, "execve failed", 1);
//	return (FAIL);
//}



//int	fd_manage(t_pipe *info, int i)
//{
//	if (i == FIRST)
//	if (pipe(info->newfd) == FAIL)
//		return (FAIL);
//	if (FIRST < i)
//	{
//		close(info->oldfd[0]);
//		close(info->oldfd[1]);
//	}
//	info->oldfd[0] = info->newfd[0];
//	info->oldfd[1] = info->newfd[1];
//	if (pipe(info->newfd) == FAIL)
//		return (FAIL);
//	dup2(info->oldfd[0], 0);
//	dup2(info->newfd[1], 1);
//	return (SUCCESS);
//}

//int	proc_operate(t_pipe info)
//{
//	int		i;
//	pid_t	pid[info.LAST];

//	i = FIRST;
//	while (i <= info.LAST)
//	{
//		fd_manage(&info, i);
//		pid[i] = fork();
//		if (pid[i] < 0)
//			error_exit(info.path, "fork failed", 1);
//		else if (!pid[i])
//			cmd_operate(info, i);
//		close(info.newfd[1]);
//		i++;
//	}
//	wait_exit(pid, info);
//	return (SUCCESS);
//}

/*proc_operate tester*/

//int	main(int argc, char **argv, char **envp)
//{
//	t_pipe	info;

//	info = correct_info(argc, argv, envp);
//	if (!info.argc)
//		return (1);
//	proc_operate(info);
//	free_path(info.path);
//}
