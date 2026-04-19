/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3_execve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:55:18 by natakaha          #+#    #+#             */
/*   Updated: 2026/04/19 18:10:28 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_cmd.h"
#include "../../includes/execution.h"
#include "../../includes/main.h"


static int	exec_search(t_token *path, char **envp, char **cmd, t_shared_info *info);
static void	exec_child_process(t_tree *branch,
				t_shared_info *info, int fd_in, int fd_out);
static int	validate_execute(int cache, char *full_path, char **cmd, char **envp);
static void	exec_search_path(t_token *env_node, char **cmd, t_shared_info *info);


int	exec_fork(t_tree *branch, t_shared_info *info, int fd_in, int fd_out)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), FAILUER);
	else if (pid > 0)
	{
		if (pid_add_back(&(info->plist), pid) == SUCCESS 
		&& env_underscore(branch->arg_list, info) == SUCCESS)
			return (SUCCESS);
		return (FAILUER);
	}
	else if (pid == 0)
		exec_child_process(branch, info, fd_in, fd_out);
	return (FAILUER);
}

static void	exec_child_process(t_tree *branch,
	t_shared_info *info, int fd_in, int fd_out)
{
	char	**cmd;

	setup_signal_child();
	manage_expander(branch, info);
	manage_exporter(branch, info);
	manage_file_descriptor(fd_in, fd_out, info, branch);
	info->envp = discard_local_env(info->envp);
	cmd = manage_arg_load(info, branch->arg_list);
	exec_search_path(info->envp, cmd, info);
}

static void	exec_search_path(t_token *env_node, char **cmd, t_shared_info *info)
{
	t_token	*path;
	char	**envp;

	path = complete_path(env_node);
	if (!path)
	{
		info->last_ecode = 2;
		builtin_exit(NULL, info);
	}
	envp = manage_arg_load(info, env_node);
	exec_search(path, envp, cmd, info);
	info->last_ecode = 2;
	builtin_exit(NULL, info);
}

static int	exec_search(t_token *path, char **envp, char **cmd, t_shared_info *info)
{
	int		cache;
	char	*full_path;
	
	cache = COMMAND_NOT_FOUND;
	while (path)
	{
		full_path = ft_strjoin(path->token, cmd[0]);
		if (!full_path)
		{
			info->last_ecode = 2;
			builtin_exit(NULL, info);
		}
		cache = validate_execute(cache, full_path, cmd, envp);
		free(full_path);
		path = path->next;
	}
	if (ft_strchr(cmd[0], '/'))
		cache = validate_execute(cache, cmd[0], cmd, envp);
	info->last_ecode = command_error_message(cmd[0], cache);
	free_split(cmd);
	free_split(envp);
	builtin_exit(NULL, info);
	return (FAILUER);
}

static int	validate_execute(int cache, char *full_path, char **cmd, char **envp)
{
	int	flag;

	flag = command_error_check(full_path);
	if (flag == SUCCESS)
		execve(full_path, cmd, envp);
	if (flag == IS_A_DIRECTORY || flag == PERMISSION_DENIED)
		return (flag);
	return (cache);
}
