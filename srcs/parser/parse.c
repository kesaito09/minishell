/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 04:00:08 by kesaitou          #+#    #+#             */
/*   Updated: 2025/12/18 10:33:51 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

static t_tree	*parse_pipeline(t_token **cur)
{
	t_tree	*pipe_node;
	t_tree	*left_node;

	left_node = parse_command(cur);
	if (!left_node)
		return (NULL);
	if (!*cur || (*cur)->type != TOKEN_PIPE)
		return (left_node);
	*cur = (*cur)->next;
	if (!*cur)
		return (free_tree_rec(left_node), NULL);
	pipe_node = tree_new(NULL, NULL, PIPE);
	if (!pipe_node)
		return (free_tree_rec(left_node), NULL);
	pipe_node->left = left_node;
	pipe_node->right = parse_command(cur);
	if (!pipe_node->right)
		return (NULL);
	return (pipe_node);
}

static t_tree	*parse_logical(t_token **cur, t_tree *left_node)
{
	t_tree	*logical_node;

	if (!*cur || ((*cur)->type != TOKEN_CONJUNCTIONE
			&& (*cur)->type != TOKEN_DISJUNCTIONE))
		return (left_node);
	if ((*cur)->type == TOKEN_CONJUNCTIONE)
		logical_node = tree_new(NULL, NULL, CONJUNCTION);
	else
		logical_node = tree_new(NULL, NULL, DISJUNCTION);
	if (!logical_node)
		return (free_tree_rec(left_node), NULL);
	logical_node->left = left_node;
	*cur = (*cur)->next;
	logical_node->right = parse_pipeline(cur);
	if (!logical_node->right)
		return (NULL);
	return (logical_node);
}

static t_tree	*parse_manage(t_token **cur)
{
	t_tree	*branch;

	branch = parse_pipeline(cur);
	if (!branch)
		return (NULL);
	while (*cur)
	{
		branch = parse_logical(cur, branch);
		if (!branch)
			return (NULL);
	}
	return (branch);
}

t_tree	*parser(char *input)
{
	t_tree	*ast;
	t_token	*token_list;
	t_token	*tmp;

	ast = NULL;
	token_list = NULL;
	if (!input || !*input)
		return (NULL);
	if (tokenizer(input, &token_list) == FAILUER)
		return (NULL);
	if (!token_list)
		return (NULL);
	tmp = token_list;
	ast = parse_manage(&token_list);
	t_lstclear(&tmp, free);
	return (ast);
}

// int	main(int argc, char **argv)
//{
//	t_token	*token;
//	t_tree	*branch;

//	if (argc < 2)
//		return (1);
//	token = NULL;
//	my_lex(argv[1], &token);
//	branch = parser(argv[1]);
//	print_tree_rec(branch);
//}
