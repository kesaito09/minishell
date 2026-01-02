/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3_char_list.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:30:23 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/02 19:14:04 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_char_list	*c_lstlast(t_char_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

size_t	c_lstsize(t_char_list *lst)
{
	size_t	len;

	if (!lst)
		return (0);
	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

void	c_lstclear(t_char_list **lst, void (*del)(void *))
{
	t_char_list	*current;
	t_char_list	*next;

    (void)del;
	current = *lst;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	(*lst) = NULL;
}

int	commit_token(t_token **token_list, t_clist **c_list, t_token_type type)
{
	char	*token;

	if (is_sub_token(type) &&(*c_list) ->sub_clist)
	{
		token = list_to_string((*c_list) ->sub_clist);
		if (!token)
			return (FAILUER);
		add_token((*token_list) ->sub_token, token, type);
	}
	if ((*c_list) ->token_clist)
	{
		token = list_to_string((*c_list) ->token_clist);
		if (!token)
			return (FAILUER);
		add_token(token_list, token, type);
	}
	return (SUCCESS);
}
