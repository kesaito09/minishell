/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 04:00:08 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/06 10:15:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

static t_tree	*parse_pipeline_rec(t_token **cur, t_tree *left_node)
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
	pipe_node->right = parse_command(cur);
	if (*cur && (*cur)->type == TOKEN_PIPE)
		pipe_node = parse_pipeline_rec(cur, pipe_node);
	if (!pipe_node->right)
		return (NULL);
	return (pipe_node);
}

static t_tree	*parse_pipeline(t_token **cur)
{
	t_tree	*node;

	node = parse_command(cur);
	node = parse_pipeline_rec(cur, node);
	return (node);
}

static t_tree	*parse_logical_rec(t_token **cur, t_tree *left_node)
{
	t_tree	*logical_node;

	if (!left_node)
		return (NULL);
	if (!*cur
		|| ((*cur)->type != TOKEN_CONJUNCTIONE
		&& (*cur)->type != TOKEN_DISJUNCTIONE))
		return (left_node);
	if ((*cur)->type == TOKEN_CONJUNCTIONE)
		logical_node = tree_new(CONJUNCTION);
	else
		logical_node = tree_new(DISJUNCTION);
	if (!logical_node)
		return (free_tree_rec(left_node), NULL);
	logical_node->left = left_node;
	*cur = (*cur)->next;
	logical_node->right = parse_pipeline(cur);
		if (*cur
			&& ((*cur)->type != TOKEN_CONJUNCTIONE
			|| (*cur)->type != TOKEN_DISJUNCTIONE))
			logical_node = parse_logical_rec(cur, logical_node);
	if (!logical_node->right)
		return (NULL);
	return (logical_node);
}


t_tree	*parse_manage(t_token **cur)
{
	t_tree *branch;

	branch = parse_pipeline(cur);
	branch = parse_logical_rec(cur, branch);
	return (branch);
}

#include <stdio.h>
static void	print_subtokens(t_token *node, int depth)
{
	while (node)
	{
		fprintf(stderr, "%*sSUB: %s -- TYPE: %d\n",
			depth * 2, "", node->token, node->type);
		node = node->next;
	}
}

void	print_tokens(t_token *node)
{
	while (node)
	{
		fprintf(stderr, "TOK: %s -- TYPE: %d\n", node->token, node->type);
		if (node->sub_token)
			print_subtokens(node->sub_token, 1);
		node = node->next;
	}
}

t_tree	*parser(char *input)
{
	t_tree	*ast;
	t_token	*token_list;
	t_token	*tmp;

	ast = NULL;
	if (!input || !*input)
		return (NULL);
	token_list = tokenizer(input);
	if (!token_list)
		return (NULL);
	// print_tokens(token_list);
	tmp = token_list;
	ast = parse_manage(&token_list);
	t_lstclear(&tmp, free);
	return (ast);
}

/*tester*/



// int	main(int argc, char **argv)
// {
// 	t_token	*token;
// 	t_tree	*branch;

// 	if (argc < 2)
// 		return (1);
// 	token = tokenizer(argv[1]);
// 	if (!token)
// 		return (1);
// 	branch = parser(argv[1]);
// 	print_token(branch->file_list);
// 	print_token(branch->arg_list);
// }
