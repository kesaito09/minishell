/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse3_logical.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 04:00:08 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/22 22:23:37 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

static t_tree	*parse_logical_rec(t_token **cur,
					t_tree *left_node, t_token *envp);

t_tree	*parse_manage(t_token **cur, t_token *envp)
{
	t_tree	*branch;

	branch = parse_pipeline(cur, envp);
	branch = parse_logical_rec(cur, branch, envp);
	return (branch);
}

static t_tree	*parse_logical_rec(t_token **cur,
					t_tree *left_node, t_token *envp)
{
	t_tree	*logical_node;

	if (!left_node)
		return (NULL);
	if (!*cur || ((*cur)->type != TOKEN_CONJUNCTIONE
			&& (*cur)->type != TOKEN_DISJUNCTIONE))
		return (left_node);
	if ((*cur)->type == TOKEN_CONJUNCTIONE)
		logical_node = tree_new(CONJUNCTION);
	else
		logical_node = tree_new(DISJUNCTION);
	if (!logical_node)
		return (free_tree_rec(&left_node), NULL);
	logical_node->left = left_node;
	free_and_skip_one(cur);
	logical_node->right = parse_pipeline(cur, envp);
	if (!logical_node->right)
		return (free_tree_rec(&logical_node), NULL);
	if (*cur && ((*cur)->type == TOKEN_CONJUNCTIONE
			|| (*cur)->type == TOKEN_DISJUNCTIONE))
		logical_node = parse_logical_rec(cur, logical_node, envp);
	return (logical_node);
}
