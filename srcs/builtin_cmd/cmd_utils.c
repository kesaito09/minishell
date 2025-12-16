/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:07:56 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/16 17:08:15 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/commands.h"
#include "../../includes/execution.h"

int	count_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

int	ft_argcmp(const char *arg, char *src)
{
	int	len;

	if (!arg)
		return (-1);
	len = ft_strlen(arg);
	return (ft_strncmp(arg, src, len));
}

int	find_arg(const char *arg, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_argcmp(arg, envp[i]))
			return (true);
		i++;
	}
	return (false);
}
