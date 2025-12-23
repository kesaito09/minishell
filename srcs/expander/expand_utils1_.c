/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils1_.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:27:47 by kesaitou          #+#    #+#             */
/*   Updated: 2025/12/22 19:40:35 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

bool	is_delimiter_variables(int c)
{
	if (c == '_' || ft_isalnum(c))
		return (false);
	return (true);
}

int	count_varibles(char *av)
{
	int len;

	len = 0;
	while (*av && is_delimiter_variables(*av))
		len++;
	return (len);
}

t_token	*search_variable(char *key, t_token *envp)
{
	while (envp)
	{
		if (!ft_strcmp(key, envp->token))
			return (envp);
		envp = envp->next;
	}
	return (NULL);
}
