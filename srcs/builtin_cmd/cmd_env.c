/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 06:29:07 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/10 01:27:03 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.h"
#include "../../includes/execution.h"

void	env(char **cmd, t_pipe *info)
{
	int	i;

	i = 0;
	if (!info->envp)
		return ;
	while (info->envp[i])
	{
		ft_putendl_fd(info->envp[i], 1);
		i++;
	}
	(void)cmd;
}