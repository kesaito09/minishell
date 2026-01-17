/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:07:56 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/17 22:09:40 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/commands.h"
#include "../../includes/execution.h"

void	invalid_message(char *arg)
{
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

int	is_valid_arg(char *arg)
{
	int	i;
	int	len;

	len = strchr_len(arg, '=');
	if (len < 0)
		return (false);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (invalid_message(arg), false);
	i = 1;
	while (i < len)
	{
		if (is_env_delimiter(arg[i]))
			return (invalid_message(arg), false);
		i++;
	}
	return (true);
}

int	ft_argcmp(const char *arg, const char *env)
{
	int	len;

	if (!arg)
		return (-1);
	len = strchr_len((char *)arg, '=');
	if (len < 0)
		len = ft_strlen(arg);
	if (ft_strncmp(arg, env, len))
		return (1);
	if (env[len] != '=')
		return (1);
	return (0);
}

int	ft_keycmp(const char *arg, const char *env)
{
	int	len;

	if (!arg)
		return (-1);
	len = ft_strlen(arg);
	if (ft_strncmp(arg, env, len))
		return (1);
	if (env[len] != '=')
		return (1);
	return (0);
}

char	*return_value(char *arg, t_token *envp)
{
	while (envp)
	{
		if (!ft_keycmp(arg, envp->token))
			return (ft_strdup(envp->token + ft_strlen(arg)));
		envp = envp->next;
	}
	return (ft_strdup(""));
}
