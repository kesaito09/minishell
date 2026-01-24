/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_tlist2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:23:28 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/24 15:18:39 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	t_lstdelone(t_token *lst, void (*del)(void *))
{
	(del)(lst->token);
	free(lst);
}

void	t_lstclear(t_token **lst, void (*del)(void *))
{
	t_token	*current;
	t_token	*next;

	current = *lst;
	while (current)
	{
		next = current->next;
		(del)(current->token);
		free(current);
		current = next;
	}
	(*lst) = NULL;
}

void	t_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*current;

	if (!lst)
		return ;
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

void	t_lstadd_front(t_token **lst, t_token *new)
{
	new->next = (*lst);
	(*lst) = new;
}

void	t_lstadd_sort(t_token **lst, t_token *new)
{
	t_token	*current;
	t_token	*pre;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	pre = NULL;
	while (current)
	{
		if (ft_strcmp(current->token, new->token) >= 0)
			break ;
		pre = current;
		current = current->next;
	}
	if (pre)
		pre->next = new;
	else
		*lst = new;
	new->next = current;
}
