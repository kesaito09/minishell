/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:25:00 by kesaitou          #+#    #+#             */
/*   Updated: 2025/12/05 23:09:10 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	buff_add_buck(t_char_list **char_list, t_char_list *new_char_list)
{
	t_char_list	*current;

	if (!char_list)
		return ;
	if (!*char_list)
		*char_list = new_char_list;
	else
	{
		current = *char_list;
		while (current ->next)
			current = current ->next;
		current ->next = new_char_list;
	}
}

void    append_char(t_char_list **list, char c)
{
    t_char_list *new_node;
    t_char_list *temp;

    new_node = malloc(sizeof(t_char_list));
    if (!new_node)
        return ;
    new_node->c = c;
    new_node->next = NULL;

    if (!*list)
    {
        *list = new_node;
    }
    else
    {
        temp = *list;
        while (temp->next)
            temp = temp->next;
        temp->next = new_node;
    }
}

char *list_to_string(t_char_list **list)
{
	char		*str;
	t_char_list *current;
	int			list_size;
	size_t		i;

	list_size = c_lstsize(*list);
	str = ft_calloc(list_size + 1, sizeof(char));
	if (!str)
		return (c_lstclear(list, free) ,NULL);
	current = *list;
	i = 0;
	while (current)
	{
		str[i] = current ->c;
		i++;
		current = current ->next;
	}
	c_lstclear(list, free);
	return (str);
}

void	add_token(t_token **token_list, char *token, t_token_type type)
{
	t_token	*last;
	t_token	*new_token;

	if (!token_list)
		return ;
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->next = NULL;
	new_token->token = token;
	new_token->type = type;
	if (!*token_list)
		*token_list = new_token;
	else
	{
		last = t_lstlast(*token_list);
		last->next = new_token;
	}
}

// t_token	*lstmap(t_token *lst, void *(*f)(void *),
// 		void (*del)(void *))
// {
// 	t_token	*begin_list;
// 	t_token	*new_elem;

// 	if (!lst)
// 		return (NULL);
// 	begin_list = lstnew((f)(lst->token));
// 	if (!begin_list)
// 		return (NULL);
// 	lst = lst->next;
// 	while (lst)
// 	{
// 		new_elem = lstnew((f)(lst->token));
// 		if (!new_elem)
// 		{
// 			lstclear(&begin_list, del);
// 			return (NULL);
// 		}
// 		lstadd_back(&begin_list, new_elem);
// 		lst = lst->next;
// 	}
// 	return (begin_list);
// }

// void	lstiter(t_token *lst, void (*f)(void *))
// {
// 	while (lst)
// 	{
// 		(f)(lst->token);
// 		lst = lst->next;
// 	}
// }
