/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:22:44 by kesaitou          #+#    #+#             */
/*   Updated: 2025/11/28 12:48:52 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lstdelone(t_token_list *lst, void (*del)(void *))
{
	(del)(lst->token);
	free(lst);
}

void	lstclear_(t_token_list **lst, void (*del)(void *))
{
	t_token_list	*current;
	t_token_list	*next;

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

