/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse4_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 19:39:10 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/17 19:39:30 by natakaha         ###   ########.fr       */
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
