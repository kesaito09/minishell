/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils1_.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:27:47 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/01 01:40:46 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expander.h"

bool	is_delimiter_variables(int c)
{
	if (c == '_' || ft_isalnum(c))
		return (true);
	return (false);
}

int	count_varibles(char *av)
{
	int len;

	len = 0;
	while (*av && is_delimiter_variables(*av))
	{
		av++;
		len++;
	}
	return (len);
}

t_token	*search_variable(char *key, t_token *envp)
{
	while (envp)
	{
		if (!ft_argcmp(key, envp->token))
			return (envp);
		envp = envp->next;
	}
	return (NULL);
}

char	*value_dup(char	*env)
{
	int	i;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (env[i] != '=')
		return (NULL);
	i++;
	return (ft_strdup(env + i));
}
