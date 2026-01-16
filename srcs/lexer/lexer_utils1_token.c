/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:25:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/16 13:31:44 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

// void	buff_add_buck(t_char_list **char_list, t_char_list *new_char_list)
// {
// 	t_char_list	*current;

// 	if (!char_list)
// 		return ;
// 	if (!*char_list)
// 		*char_list = new_char_list;
// 	else
// 	{
// 		current = *char_list;
// 		while (current->next)
// 			current = current->next;
// 		current->next = new_char_list;
// 	}
// }

// int	append_char(t_char_list **list, char c)
// {
// 	t_char_list	*new_node;
// 	t_char_list	*temp;

// 	new_node = ft_calloc(sizeof(t_char_list), 1);
// 	if (!new_node)
// 		return (FAILUER);
// 	new_node->c = c;
// 	new_node->next = NULL;
// 	c_lstadd_back(list, new_node);
// 	return (SUCCESS);
// }

// char	*list_to_string(t_char_list *c_list)
// {
// 	char		*str;
// 	int			list_size;
// 	size_t		i;

// 	list_size = c_lstsize(c_list);
// 	str = ft_calloc(list_size + 1, sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	while (c_list)
// 	{
// 		str[i++] = c_list->c;
// 		c_list = c_list->next;
// 	}
// 	return (str);
// }

// int	add_token(t_token **token_list, char *token, t_token_type type)
// {
// 	t_token	*new_token;

// 	if (!token)
// 		return (FAILUER);
// 	new_token = ft_calloc(1, sizeof(t_token));
// 	if (!new_token)
// 		return (FAILUER);
// 	new_token->next = NULL;
// 	new_token->token = token;
// 	new_token->type = type;
// 	new_token ->sub_token = NULL;
// 	if (!*token_list)
// 		*token_list = new_token;
// 	else
// 		t_lstadd_back(token_list, new_token);
// 	return (SUCCESS);
// }


