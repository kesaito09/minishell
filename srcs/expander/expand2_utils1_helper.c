/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2_utils1_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 03:25:14 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/10 20:42:57 by kesaitou         ###   ########.fr       */
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
	return (value_dup(var->token));
}

int	ft_strchr_len_set(char *str, char *set)
{
	int	len;

	len = 0;
	while (str[len] && !ft_strchr(set, str[len]))
		len++;
	return (len);
}

void	free_token_list(t_token *list)
{
	t_token	*next_node;

	while (list)
	{
		next_node = list->next;
		if (list->sub_token)
			free_token_list(list->sub_token);
		free(list->token);
		free(list);
		list = next_node;
	}
}
