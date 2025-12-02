/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 19:30:23 by kesaitou          #+#    #+#             */
/*   Updated: 2025/12/02 20:39:41 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

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
