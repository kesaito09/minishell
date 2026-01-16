/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 19:38:09 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/16 14:10:17 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expander.h"
#include <stdio.h>

void	print_sub_token(t_token *sub)
{
	while (sub)
	{
		fprintf(stderr, "--SUB: %s   TYPE: %d--\n", sub->token, sub->type);
		sub = sub->next;
	}
}

void	print_token(t_token *token)
{
	while (token)
	{
		fprintf(stderr, "--TOKEN: %s  TYPE: %d--\n", token->token, token->type);
		// if (token->sub_token)
		// {
		// 	print_sub_token(token->sub_token);
		// }
		token = token->next;
	}
}

void	free_tlist_deep(t_token *list)
{
	t_token	*next_node;

	while (list)
	{
		next_node = list->next;
		if (list->sub_token)
			free_tlist_deep(list->sub_token);
		free(list->token);
		free(list);
		list = next_node;
	}
}

int	expander(t_token **token_list, t_pipe *info, t_list_type type)
{
	if (expand_token(token_list, info) == FAILUER)
		return (free_tlist_deep(*token_list), FAILUER);
	if (path_name_expantion(token_list, type) == FAILUER)
		return (free_tlist_deep(*token_list), FAILUER);
	return (SUCCESS);
}
