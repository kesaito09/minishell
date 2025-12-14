/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 06:21:49 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/10 01:26:41 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.h"
#include "../../includes/execution.h"

static int	count_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

int	export(char **cmd, t_pipe *info)
{
	char	**new_env;
	char	*tmp;
	int		i;

	i = count_env(info->envp);
	tmp = ft_strchr(cmd[1], '=');
	if (!tmp || tmp == cmd[1])
		return (ERROR);
	new_env = (char **)ft_calloc(sizeof(char *), i + 2);
	new_env[i] = ft_strdup(cmd[1]);
	while (i >= 0)
	{
		i--;
		new_env[i] = ft_strdup(info->envp[i]);
	}
	info->envp = new_env;
	return (SUCCESS);
}
