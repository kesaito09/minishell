/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3_left_join.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 08:30:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/05 08:30:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

static t_tree_type	node_type(t_token *cur)
{
	if (cur->type == TOKEN_PIPE)
		return (PIPE);
	if (cur->type == TOKEN_CONJUNCTIONE)
		return (CONJUNCTION);
	if (cur->type == TOKEN_DISJUNCTIONE)
		return (DISJUNCTION);
	return (NONE);
}

static bool	is_op_at_level(t_token *cur, t_op_level level)
{
	if (!cur)
		return (false);
	if (level == OP_LOGICAL)
		return (cur->type == TOKEN_CONJUNCTIONE
			|| cur->type == TOKEN_DISJUNCTIONE);
	if (level == OP_PIPELINE)
		return (cur->type == TOKEN_PIPE);
	return (false);
}

t_tree	*parse_left_join(t_token **cur, t_shared_info *info, t_op_level level)
{
	t_tree	*left;
	t_tree	*node;

	if (level == OP_COMMAND)
		return (parse_command(cur, info));
	left = parse_left_join(cur, info, level + 1);
	while (left && is_op_at_level(*cur, level))
	{
		node = tree_new(node_type(*cur));
		if (!node)
			return (free_tree_rec(&left), NULL);
		node->left = left;
		free_and_skip_one(cur);
		node->right = parse_left_join(cur, info, level + 1);
		if (!node->right)
			return (free_tree_rec(&node), NULL);
		left = node;
	}
	return (left);
}
