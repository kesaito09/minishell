/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 03:25:14 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/08 05:33:58 by kesaitou         ###   ########.fr       */
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
	return (ft_strdup(var));
}

int	ft_strchr_len_set(char *str, char *set)
{
	char	*check;
	int		len;

	len = 0;
	if (!str || !ft_strchr(set, str[len]))
		return (-1);
	while (str[len] && ft_strchr(set, str[len]))
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
	len = 0;
	while (*token)
	{
		len = ft_strchr_len_set(set, *token);
		if (len < 0)
			new_token = ft_strdup(token);
		else if (len == 0)
		{
			skip_set(&token, set);
			continue;
		}
		else
			new_token = ft_strndup(token, len);
		if (!new_token)
			return (FAILUER);
		new_node = t_lstnew(new_token, type);
		if (!new_node)
			return (FAILUER);
		t_lstadd_back(new_tlist, new_node);
		if (len < 0)
			break;
		token += len;
	}
}

int merge_tlist(t_token **sub_token, char *set)
{
	t_token	*new_lst;
	t_token	*cur;
	t_token	*next;

	if (!sub_token)
		return (FAILUER);	
	while (*sub_token)
	{
		cur = *sub_token;
		if ((*sub_token) ->type != SUB_TOKEN_DOLLAR)
		{
			*sub_token = (*sub_token) ->next;
			continue;
		}
		next = cur ->next;
		new_lst = string_to_tlist((*sub_token), set, SUB_TOKEN_DOLLAR);
		if (!new_lst)
			return (FAILUER);
		
		
	}
	
	
	
	
}

t_token	*split_to_tlist(t_token *token, char *set)
{
	while (token)
	{
		
	}
}