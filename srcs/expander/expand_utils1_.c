/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils1_.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:27:47 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/08 03:27:28 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expander.h"

int	count_varibles(char *av)
{
	int	len;

	len = 0;
	while (av[len] && !is_delimiter_variables(av[len]))
		len++;
	return (len);
}

t_token	*search_variable(char *key, t_token *envp)
{
	while (envp)
	{
		if (!ft_keycmp(key, envp->token))
			return (envp);
		envp = envp->next;
	}
	return (NULL);
}

char	*value_dup(char *env)
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

bool	is_dollar(t_token_type type)
{
	if (type == SUB_TOKEN_DOLLAR || type == SUB_TOKEN_DOLLAR_DQUOTE)
		return (true);
	return (false);
}

bool	is_ifs(char *ifs, int c)
{
	if (ft_strchr(ifs, c))
		return (true);
	return (false);
}

