/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 19:39:10 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/23 09:12:07 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

t_tree	*parser(t_shared_info *info)
{
	t_tree	*branch;
	t_token	*token_list;
	char	*input;

	branch = NULL;
	input = info->input->token;
	if (!input)
		return (NULL);
	token_list = tokenizer(input);
	free_and_skip_one(&info->input);
	if (!token_list)
		return (NULL);
	branch = parse_manage(&token_list, info);
	if (branch && token_list)
	{
		syntax_error_msg(token_list->token);
		free_tree_rec(&branch);
		t_lstclear(&token_list, free);
		return (NULL);
	}
	if (token_list)
		t_lstclear(&token_list, free);
	return (branch);
}

//int	main(int ac, char **av)
//{
//	t_tree	*ast;

//	ast = parser(av[1]);
//	free_tree_rec(ast);
//	(void)ac;
//	(void)av;

//	return (0);
//}
