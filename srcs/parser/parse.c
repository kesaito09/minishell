/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 04:00:08 by kesaitou          #+#    #+#             */
/*   Updated: 2025/12/16 21:54:21 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

static t_tree	*parse_pipeline(t_token **cur)
{
	t_tree	*left_node;
	t_tree	*pipe_node;

	left_node = parse_command(cur);
	if (!left_node)
		return (NULL);
	while (*cur && (*cur)->type == TOKEN_PIPE)
	{
		pipe_node = tree_new(NULL, NULL, PIPE);
		if (!pipe_node)
		return (NULL);
		pipe_node->left = left_node;
		*cur = (*cur)->next;
		pipe_node->right = parse_pipeline(cur);
		if (!pipe_node->right)
		return (NULL);
		return (pipe_node);
	}
	return (left_node);
}

static t_tree	*parse_logical(t_token **cur)
{
	t_tree	*logical_node;
	t_tree	*left_node;

	left_node = parse_pipeline(cur);
	if (!left_node)
	return (NULL);
	while (*cur 
			&& ((*cur)->type == TOKEN_CONJUNCTIONE
			|| (*cur)->type == TOKEN_DISJUNCTIONE))
		{
			if ((*cur)->type == TOKEN_CONJUNCTIONE)
			logical_node = tree_new(NULL, NULL, CONJUNCTION);
			else
			logical_node = tree_new(NULL, NULL, DISJUNCTION);
			logical_node->left = left_node;
			*cur = (*cur)->next;
			logical_node->right = parse_logical(cur);
			if (!logical_node->right)
				return (NULL);
			return (logical_node);
		}
		return (left_node);
}

t_tree	*parser(char *input)
{
	t_tree	*ast;
	t_token	*token_list;
	t_token	*cur_token;

	ast = NULL;
	token_list = NULL;
	if (!input || !*input)
		return (NULL);
	my_lex(input, &token_list);
	cur_token = token_list;
	ast = parse_logical(&cur_token);
	t_lstclear(&token_list, free);
	return (ast);
}
