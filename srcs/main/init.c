/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 00:00:00 by natakaha          #+#    #+#             */
/*   Updated: 2026/04/20 00:00:00 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_shlvl(t_shared_info *info);

t_shared_info	collect_info(char **envp)
{
	t_shared_info	info;

	ft_bzero(&info, sizeof(t_shared_info));
	info.fd[0] = -1;
	info.fd[1] = -1;
	info.fd_stdout = dup(1);
	info.fd_stdin = dup(0);
	if (info.fd_stdout < 0 || info.fd_stdin < 0)
		fatal_exit(&info);
	info.envp = argv_token(envp);
	if (!info.envp)
		fatal_exit(&info);
	env_shlvl(&info);
	env_exit_code(0, SUCCESS, &info);
	return (info);
}
