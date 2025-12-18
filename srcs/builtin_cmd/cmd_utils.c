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

int	ft_argcmp(const char *arg, char *src)
{
	int	len;

	if (!arg)
		return (-1);
	len = ft_strlen(arg);
	if (ft_strncmp(arg, src, len))
		return (1);
	if (src[len] != '=')
		return (1);
	return (0);
}

bool	find_arg(const char *arg, char **envp)
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
