/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3_execve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:55:18 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/25 06:35:01 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_cmd.h"
#include "../../includes/execution.h"
#include <stdio.h>

static int	exec_search(char **envp, char **cmd);
static int	exec_cmd_module(t_tree *branch,
				t_shared_info *info, int fd_in, int fd_out);

int	exec_cmd(t_tree *branch, t_shared_info *info, int fd_in, int fd_out)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), FAILUER);
	if (pid > 0)
		return (pid_add_back(&(info->plist), pid),
			env_underscore(branch->arg_list, info));
	setup_signal_child();
	close_unused_pipe(fd_in, fd_out, info->fd);
	exec_cmd_module(branch, info, fd_in, fd_out);
	exit(1);
}

static int	exec_cmd_module(t_tree *branch,
	t_shared_info *info, int fd_in, int fd_out)
{
	char	**cmd;
	char	**env;

	if (dup2_stdin_out(fd_in, fd_out) == FAILUER
		|| expander(branch->arg_list, info, ARG_LIST) == FAILUER
		|| expander(branch->env_list, info, ENV_LIST) == FAILUER
		|| expander(branch->file_list, info, FILE_LIST) == FAILUER
		|| manage_redirect(branch->file_list) == FAILUER
		|| silent_export(branch->env_list, info, TOP, 0) == FAILUER
		|| env_underscore(branch->arg_list, info) == FAILUER
		|| !branch->arg_list)
		return (FAILUER);
	cmd = token_argv(branch->arg_list);
	info->envp = discard_local_env(info->envp);
	if (!info->envp)
		return (FAILUER);
	env = token_argv(info->envp);
	if (!cmd || !env)
		return (free_split(cmd), free_split(env), FAILUER);
	exec_search(env, cmd);
	return (FAILUER);
}

static int	exec_search(char **envp, char **cmd)
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
			return (FAILUER);
		execve(full_path, cmd, envp);
		free(full_path);
		path = path->next;
	}
	command_error_check(cmd[0], path);
	execve(cmd[0], cmd, envp);
	return (FAILUER);
}

int	env_underscore(t_token *node, t_shared_info *info)
{
	char	*str;
	t_token	*tmp;

	if (!node)
		return (FAILUER);
	node = t_lstlast(node);
	str = ft_strjoin("_=", node->token);
	if (!str)
		return (FAILUER);
	tmp = t_lstnew(str, free);
	if (!tmp)
		return (FAILUER);
	if (silent_export(tmp, info, TOP, 0) == FAILUER)
		return (t_lstclear(&tmp, free), FAILUER);
	return (t_lstclear(&tmp, free), SUCCESS);
}
