/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 03:25:14 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/07 23:57:54 by kesaitou         ###   ########.fr       */
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
	return (ft_strdup(var ->token));
}

int	ft_strchr_len_set(char *str, char *set)
{
	int		len;

	len = 0;
	while (str[len] && !ft_strchr(set, str[len]))
		len++;
	return (len);
}

static void	skip_set(char **str, char *set)
{
	while (**str && ft_strchr(set, **str))
		(*str)++;
}


t_token	*string_to_tlist(char *token, char *set, t_token_type type)
{
	t_token	*new_tlist;
	t_token	*new_node;
	char	*new_token;
	int		len;

	new_tlist = NULL;
	while (*token)
	{
		skip_set(&token, set);
		if (!*token)
			break;		
		len = ft_strchr_len_set(token, set);
		new_token = new_token = ft_strndup(token, len);
		if (!new_token)
			return (NULL);
		new_node = t_lstnew(new_token, type);
		if (!new_node)
			return (NULL);
		t_lstadd_back(&new_tlist, new_node);
		token += len;
	}
	return (new_tlist);
}

int merge_tlist(t_token **sub_token, char *set)
{
	t_token	*new_lst;
	t_token	*cur;
	t_token	*next;

	if (!sub_token || !set)
		return (FAILUER);	
	while (*sub_token)
	{
		cur = *sub_token;
		if (cur ->type != SUB_TOKEN_DOLLAR)
		{
			sub_token = &cur ->next;
			continue;
		}
		next = cur ->next;
		new_lst = string_to_tlist(cur ->token, set, SUB_TOKEN_GENERAL);
		if (!new_lst)
			return (FAILUER);
		*sub_token = new_lst;
		t_lstlast(new_lst) ->next = next;
		free(cur ->token);
		free(cur);
		sub_token = &t_lstlast(new_lst) ->next;
	}
	return (SUCCESS);
}

// t_token	*split_to_tlist(t_token *token, char *set)
// {
// 	while (token)
// 	{
		
// 	}
// }