/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:23:28 by kesaitou          #+#    #+#             */
/*   Updated: 2025/11/28 15:20:04 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lstsize(t_token_list *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

t_token_list	*lstnew(char *token)
{
	t_token_list	*new_elem;

	new_elem = malloc(sizeof(t_token_list));
	if (!new_elem)
		return (NULL);
	new_elem->token = token;
	new_elem->next = NULL;
	return (new_elem);
}

t_token_list	*lstlast(t_token_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	lstadd_back(t_token_list **lst, t_token_list *new)
{
	t_token_list	*current;

	if (!*lst)
		*lst = new;
	else
	{
		current = *lst;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

void	lstadd_front(t_token_list **lst, t_token_list *new)
{
	new->next = (*lst);
	(*lst) = new;
}
