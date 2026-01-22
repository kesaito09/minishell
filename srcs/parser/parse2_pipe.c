/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 04:00:08 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/23 05:11:01 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

static t_tree	*parse_pipeline_rec(t_token **cur,
					t_tree *left_node, t_shared_info *info);

t_tree	*parse_pipeline(t_token **cur, t_shared_info *info)
{
	t_tree	*node;

	node = parse_command(cur, info);
	return (parse_pipeline_rec(cur, node, info));
}

static t_tree	*parse_pipeline_rec(t_token **cur,
					t_tree *left_node, t_shared_info *info)
{
	t_tree	*pipe_node;

	if (!left_node)
		return (NULL);
	if (!*cur || (*cur)->type != TOKEN_PIPE)
		return (left_node);
	free_and_skip_one(cur);
	if (!*cur)
		return (syntax_error_msg("newline"), free_tree_rec(&left_node), NULL);
	pipe_node = tree_new(PIPE);
	if (!pipe_node)
		return (free_tree_rec(&left_node), NULL);
	pipe_node->left = left_node;
	pipe_node->right = parse_command(cur, info);
	if (!pipe_node->right)
		return (free_tree_rec(&pipe_node), NULL);
	if (*cur && (*cur)->type == TOKEN_PIPE)
		return (parse_pipeline_rec(cur, pipe_node, info));
	return (pipe_node);
}
