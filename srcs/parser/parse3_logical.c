/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3_logical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 04:00:08 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/01 17:29:32 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

// static t_tree	*parse_logical_rec(t_token **cur, t_tree *left_node,
// 					t_shared_info *info);

// t_tree	*parse_manage(t_token **cur, t_shared_info *info)
// {
// 	t_tree	*branch;

// 	branch = parse_pipeline(cur, info);
// 	branch = parse_logical_rec(cur, branch, info);
// 	return (branch);
// }

t_tree	*parse_logical(t_token **cur, t_shared_info *info)
{
	t_tree	*logical;
	t_tree	*left;

	left = parse_pipeline(cur, info);
	while (left && *cur && ((*cur)->type == TOKEN_CONJUNCTIONE
			|| (*cur)->type == TOKEN_DISJUNCTIONE))
	{
		if ((*cur)->type == TOKEN_CONJUNCTIONE)
			logical = tree_new(CONJUNCTION);
		else
			logical = tree_new(DISJUNCTION);
		if (!logical)
			return (free_tree_rec(&left), NULL);
		logical->left = left;
		free_and_skip_one(cur);
		logical->right = parse_pipeline(cur, info);
		if (!logical->right)
			return (free_tree_rec(&logical), NULL);
		left = logical;
	}
	return (left);
}

// static t_tree	*parse_logical_rec(t_token **cur, t_tree *left_node,
// 		t_shared_info *info)
// {
// 	t_tree	*logical_node;

// 	if (!left_node)
// 		return (NULL);
// 	if (!*cur || ((*cur)->type != TOKEN_CONJUNCTIONE
// 			&& (*cur)->type != TOKEN_DISJUNCTIONE))
// 		return (left_node);
// 	if ((*cur)->type == TOKEN_CONJUNCTIONE)
// 		logical_node = tree_new(CONJUNCTION);
// 	else
// 		logical_node = tree_new(DISJUNCTION);
// 	if (!logical_node)
// 		return (free_tree_rec(&left_node), NULL);
// 	logical_node->left = left_node;
// 	free_and_skip_one(cur);
// 	logical_node->right = parse_pipeline(cur, info);
// 	if (!logical_node->right)
// 		return (free_tree_rec(&logical_node), NULL);
// 	if (*cur && ((*cur)->type == TOKEN_CONJUNCTIONE
// 			|| (*cur)->type == TOKEN_DISJUNCTIONE))
// 		logical_node = parse_logical_rec(cur, logical_node, info);
// 	return (logical_node);
// }
