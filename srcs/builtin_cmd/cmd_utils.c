/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:07:56 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/06 00:16:48 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/commands.h"
#include "../../includes/execution.h"


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

int	cmd_check(t_token *cmd)
{
	t_token *env;

	env = cmd->next;
	if (!env)
		return (FAILUER);
	if (strchr_len(env->token, '=') == 0)
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(env->token, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (FAILUER);
	}
	if (!strchr(env->token, '='))
		return (FAILUER);
	return (SUCCESS);
}
