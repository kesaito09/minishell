/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 19:39:10 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/17 15:27:05 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

t_tree	*parser(char *input, t_shared_info *info)
{
	t_tree	*ast;
	t_token	*token_list;

	ast = NULL;
	if (!input || !*input)
		return (NULL);
	token_list = tokenizer(input);
	if (!token_list)
		return (NULL);
	ast = parse_manage(&token_list, info->envp);
	return (ast);
}


int main(int ac, char **av)
{
	t_tree *ast;

	ast = parser(av[1], NULL);
	(void)ast;
	(void)ac;
	(void)av;
	ft_dprintf(2, "fpritnf");
	return (0);
	
}