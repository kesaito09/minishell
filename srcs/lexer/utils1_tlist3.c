/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_tlist3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 18:00:46 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/21 18:02:57 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_token	*t_lstlast(t_token *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

int	t_lstnew_add_back(t_token **lst, char *input, int i, t_token_type type)
{
	t_token	*node;

	node = f_lstnew(ft_strndup(input, i), type);
	if (!node)
		return (FAILUER);
	t_lstadd_back(lst, node);
	return (SUCCESS);
}
