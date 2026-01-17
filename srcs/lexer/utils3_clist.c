/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3_clist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:30:23 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/17 17:18:59 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_char_list	*c_lstlast(t_char_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	c_lstadd_back(t_char_list **lst, t_char_list *new)
{
	t_char_list	*last;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = c_lstlast(*lst);
	last->next = new;
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

