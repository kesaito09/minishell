/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_iterate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:25:00 by kesaitou          #+#    #+#             */
/*   Updated: 2025/11/28 12:50:09 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_list	*lstmap(t_token_list *lst, void *(*f)(void *),
		void (*del)(void *))
{
	t_token_list	*begin_list;
	t_token_list	*new_elem;

	if (!lst)
		return (NULL);
	begin_list = lstnew((f)(lst->token));
	if (!begin_list)
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		new_elem = lstnew((f)(lst->token));
		if (!new_elem)
		{
			lstclear(&begin_list, del);
			return (NULL);
		}
		lstadd_back(&begin_list, new_elem);
		lst = lst->next;
	}
	return (begin_list);
}

void	lstiter(t_token_list *lst, void (*f)(void *))
{
	while (lst)
	{
		(f)(lst->token);
		lst = lst->next;
	}
}
