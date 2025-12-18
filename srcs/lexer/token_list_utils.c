/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:23:28 by kesaitou          #+#    #+#             */
/*   Updated: 2025/12/09 20:02:26 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

//size_t	t_lstsize(t_token *lst)
//{
//	int	len;

//	len = 0;
//	while (lst)
//	{
//		len++;
//		lst = lst->next;
//	}
//	return (len);
//}

/*lexer用に改造した*/
t_token	*t_lstnew(char *token)
{
	t_token	*new_elem;

	new_elem = ft_calloc(sizeof(t_token), 1);
	if (!new_elem)
		return (NULL);
	new_elem ->type = TOKEN_EOF;
	new_elem->token = token;
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

// void	t_lstadd_front(t_token **lst, t_token *new)
// {
// 	new->next = (*lst);
// 	(*lst) = new;
// }
