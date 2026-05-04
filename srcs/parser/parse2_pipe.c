/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 04:00:08 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/01 19:44:43 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

// static t_tree	*parse_pipeline_rec(t_token **cur,
// 					t_tree *left_node, t_shared_info *info);

t_tree	*parse_pipeline(t_token **cur, t_shared_info *info)
{
	t_tree	*left;
	t_tree	*pipe_node;

	left = parse_command(cur, info);
	while (left && *cur && (*cur)->type == TOKEN_PIPE)
	{
		free_and_skip_one(cur);
		if (!*cur)
			return (err_syntax(info, NULL), free_tree_rec(&left), NULL);
		pipe_node = tree_new(PIPE);
		if (!pipe_node)
			return (free_tree_rec(&left), NULL);
		pipe_node->left = left;
		pipe_node->right = parse_command(cur, info);
		if (!pipe_node->right)
			return (free_tree_rec(&pipe_node), NULL);
		left = pipe_node;
	}
	return (left);
}

// static t_tree	*parse_pipeline_rec(t_token **cur,
// 					t_tree *left_node, t_shared_info *info)
// {
// 	t_tree	*pipe_node;

// 	if (!left_node)
// 		return (NULL);
// 	if (!*cur || (*cur)->type != TOKEN_PIPE)
// 		return (left_node);
// 	free_and_skip_one(cur);
// 	if (!*cur)
// 		return (err_syntax(info, NULL), free_tree_rec(&left_node), NULL);
// 	pipe_node = tree_new(PIPE);
// 	if (!pipe_node)
// 		return (free_tree_rec(&left_node), NULL);
// 	pipe_node->left = left_node;
// 	pipe_node->right = parse_command(cur, info);
// 	if (!pipe_node->right)
// 		return (free_tree_rec(&pipe_node), NULL);
// 	if (*cur && (*cur)->type == TOKEN_PIPE)
// 		return (parse_pipeline_rec(cur, pipe_node, info));
// 	return (pipe_node);
// }
