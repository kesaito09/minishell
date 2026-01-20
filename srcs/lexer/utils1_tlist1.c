/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_tlist1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:23:28 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/20 23:36:13 by natakaha         ###   ########.fr       */
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

t_token	*t_lstinsert(t_token *lst, t_token *new)
{
	t_token	*tmp;
	t_token	*last;

	if (!lst || !new)
		return (NULL);
	last = new;
	while (last->next)
		last = last->next;
	free(lst->token);
	tmp = lst->next;
	lst->token = new->token;
	lst->next = new->next;
	t_lstadd_back(&lst, tmp);
	free(new);
	return (last->next);
}

t_token	*t_lstnew(char *token, void (*del)(void *))
{
	t_token	*new_elem;

	if (!token)
		return (NULL);
	new_elem = ft_calloc(sizeof(t_token), 1);
	if (!new_elem)
		return (del(token), NULL);
	new_elem->token = token;
	new_elem->next = NULL;
	return (new_elem);
}

t_token	*f_lstnew(char *token, t_token_type type)
{
	t_token	*new_file;

	if (!token)
		NULL;
	new_file = t_lstnew(token, free);
	if (!new_file)
		return (free(token), NULL);
	new_file->type = type;
	return (new_file);
}
