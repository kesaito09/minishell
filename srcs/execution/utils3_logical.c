/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_logical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 09:14:04 by naoki             #+#    #+#             */
/*   Updated: 2026/01/23 04:50:42 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	close_unused_pipe(int fd_in, int fd_out, int pipes[2])
{
	if (pipes[0] >= 0 && pipes[0] != fd_in)
		close(pipes[0]);
	if (pipes[1] >= 0 && pipes[1] != fd_out)
		close(pipes[1]);
}

int	dup2_stdin_out(int fd_in, int fd_out)
{
	if (fd_in >= 0)
		if (dup2(fd_in, 0) == FAILUER)
			return (FAILUER);
	if (fd_out >= 0)
		if (dup2(fd_out, 1) == FAILUER)
			return (FAILUER);
	return (SUCCESS);
}

int	reset_stdin_out(t_shared_info *info)
{
	return (dup2_stdin_out(info->fd_stdin, info->fd_stdout));
}

t_token	*discard_local_env(t_token *envp)
{
	t_token	*new_env;
	t_token	*tmp;

	new_env = NULL;
	while (envp)
	{
		if (envp->type != 0)
		{
			free_and_skip_one(&envp);
			continue ;
		}
		tmp = envp->next;
		envp->next = NULL;
		t_lstadd_back(&new_env, envp);
		envp = tmp;
	}
	return (new_env);
}
