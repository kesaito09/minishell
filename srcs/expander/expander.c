/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 19:38:09 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/11 13:30:15 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expander.h"

#include <stdio.h>

void	print_sub_token(t_token *sub)
{
	while (sub)
	{
		fprintf(stderr, "--SUB: %s   TYPE: %d--\n", sub ->token, sub ->type);
		sub = sub ->next;
	}
}

void	print_token(t_token *token)
{
	while (token)
	{
		if (token ->sub_token)
		{
			print_sub_token(token ->sub_token);
		}
		token = token ->next;
	}
}

int path_name_expantion(t_token **token_list, t_list_type type)
{
	t_token	*tmp;
	int		n;

	tmp = *token_list;
	while (tmp)
	{
		n = insert_token(tmp, wild_card, tmp->sub_token);
		if (type == FILE_LIST && n > 1)
		{
			ft_putendl_fd("ambiguous redirect", 2);
			return (FAILUER);
		}
		tmp = t_lstmove(tmp, n);
	}
	return (SUCCESS);
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

int	expander(t_token **token_list, t_token *envp, t_list_type type)
{

	if (expand_token(token_list, envp) == FAILUER)
		return (free_tlist_deep(*token_list), FAILUER);
	if (path_name_expantion(token_list, type) == FAILUER)
		return (FAILUER);
	return (SUCCESS);
}
