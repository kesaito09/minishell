/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 19:39:10 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/17 20:29:27 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

t_tree	*parser(char *input)
{
	t_tree	*ast;
	t_token	*token_list;

	ast = NULL;
	if (!input || !*input)
		return (NULL);
	token_list = tokenizer(input);
	if (!token_list)
		return (NULL);
	ast = parse_manage(&token_list);
	if (ast && token_list)
	{
		syntax_error_msg(token_list->token);
		free_tree_rec(ast);
		deep_token_clear(token_list);
		return (NULL);
	}
	if (token_list)
		deep_token_clear(token_list);
	return (ast);
}

int main(int ac, char **av)
{
	t_tree *ast;

	ast = parser(av[1]);
	free_tree_rec(ast);
	(void)ac;
	(void)av;

	return (0);
	
}
