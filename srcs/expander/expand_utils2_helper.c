/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 03:25:14 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/08 09:33:19 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expander.h"

char	*setup_ifs(t_token *envp)
{
	t_token	*var;

	var = search_variable("IFS", envp);
	if (!var)
		return (ft_strdup(" \n\t"));
	return (ft_strdup(var->token));
}

int	ft_strchr_len_set(char *str, char *set)
{
	int	len;

	len = 0;
	while (str[len] && !ft_strchr(set, str[len]))
		len++;
	return (len);
}

void	skip_set(char **str, char *set)
{
	while (**str && ft_strchr(set, **str))
		(*str)++;
}
