/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2_tlist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:23:28 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/15 20:10:19 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

size_t	t_lstsize(t_token *lst)
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

t_token	*t_lstmove(t_token *lst, int n)
{
	while (n > 0 && lst)
	{
		lst = lst->next;
		n--;
	}
	return (lst);
}

t_token	*t_lstnew(char *token)
{
	t_token	*new_elem;
	char	*dest;

	if (!token)
		return (NULL);
	new_elem = ft_calloc(sizeof(t_token), 1);
	if (!new_elem)
		return (NULL);
	dest = ft_strdup(token);
	if (!dest)
		return (free(new_elem), NULL);
	new_elem->token = dest;
	new_elem->next = NULL;
	return (new_elem);
}

t_token	*t_lstlast(t_token *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

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
