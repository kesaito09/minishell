/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 04:00:08 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/17 20:29:34 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

static t_tree	*parse_pipeline_rec(t_token **cur, t_tree *left_node,
		t_token *envp)
{
	t_tree	*pipe_node;

	if (!left_node)
		return (NULL);
	if (!*cur || (*cur)->type != TOKEN_PIPE)
		return (left_node);
	*cur = (*cur)->next;
	if (!*cur)
		return (free_tree_rec(left_node), NULL);
	pipe_node = tree_new(PIPE);
	if (!pipe_node)
		return (free_tree_rec(left_node), NULL);
	pipe_node->left = left_node;
	pipe_node->right = parse_command(cur, envp);
	if (*cur && (*cur)->type == TOKEN_PIPE)
		pipe_node = parse_pipeline_rec(cur, pipe_node, envp);
	if (!pipe_node->right)
		return (NULL);
	return (pipe_node);
}

t_tree	*parse_pipeline(t_token **cur, t_token *envp)
{
	t_tree	*node;

	node = parse_command(cur, envp);
	node = parse_pipeline_rec(cur, node, envp);
	return (node);
}
