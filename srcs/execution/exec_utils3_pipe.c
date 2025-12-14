/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 09:14:04 by naoki             #+#    #+#             */
/*   Updated: 2025/12/10 00:11:06 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

/*initial num of fd == -1*/

//int	pipe_update(int	fd_in[2], int fd_out[2])
//{
//	if (fd_in[0] >= 0)
//	{
//		close(fd_in[0]);
//		fd_in[0] = -1;
//	}
//	if (fd_in[1] >= 0)
//	{
//		close(fd_in[1]);
//		fd_in[1] = -1;
//	}
//	if (fd_out[0] >= 0)
//		fd_in[0] = fd_out[0];
//	if (fd_out[1] >= 0)
//		fd_in[1] = fd_out[1];
//	if (pipe(fd_out) == FAILUER)
//		return (FAILUER);
//	return (SUCCESS);
//}

//int	pipe_terminate(int	fd_in[2], int fd_out[2])
//{
//	if (fd_in[0] >= 0)
//	{
//		close(fd_in[0]);
//		fd_in[0] = -1;
//	}
//	if (fd_in[1] >= 0)
//	{
//		close(fd_in[1]);
//		fd_in[1] = -1;
//	}
//	if (fd_out[0] >= 0)
//		fd_in[0] = fd_out[0];
//	if (fd_out[1] >= 0)
//		fd_in[1] = fd_out[1];
//	fd_out[0] = -1;
//	fd_out[1] = -1;
//	return (SUCCESS);
//}

//void	close_fd_in_out(int *fd_in, int *fd_out)
//{
//	if (*fd_in >= 0)
//		close(*fd_in);
//	*fd_in = -1;
//	if (*fd_out >= 0)
//		close(*fd_out);
//	*fd_out = -1;
//}

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

int	reset_stdin_out(t_pipe *info)
{
	return (dup2_stdin_out(info->fd_stdin, info->fd_stdout));
}

