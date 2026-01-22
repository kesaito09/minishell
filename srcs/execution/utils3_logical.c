/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_logical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 09:14:04 by naoki             #+#    #+#             */
/*   Updated: 2026/01/23 01:18:58 by natakaha         ###   ########.fr       */
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
	t_token	*trash;
	t_token	*tmp;

	new_env = NULL;
	trash = NULL;
	while (envp)
	{
		tmp = envp;
		tmp->next = NULL;
		if (envp->type == 0)
			t_lstadd_back(&new_env, tmp);
		if (envp->type == 1)
			t_lstadd_back(&trash, tmp);
		envp = envp->next;
	}
	t_lstclear(&trash, free);
	return (new_env);
}
