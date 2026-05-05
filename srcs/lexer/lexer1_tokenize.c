/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:22:47 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/06 00:00:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static void	*clear_and_fatal_exit(t_token **lst, t_shared_info *info)
{
	t_lstclear(lst, free);
	fatal_exit(info);
	return (NULL);
}

static int	token_len(char *input, t_token_type type)
{
	if (type == TOKEN_WORD)
		return (shell_word_len(input));
	if (type == TOKEN_SPACE)
		return (1);
	return (operator_len(input));
}

t_token	*tokenizer(char *input, t_shared_info *info)
{
	t_token			*lst;
	t_token_type	type;
	int				n;

	lst = NULL;
	while (*input)
	{
		type = str_type(input);
		n = token_len(input, type);
		if (n == FAILURE)
			return (t_lstclear(&lst, free), NULL);
		if (type == TOKEN_SPACE)
		{
			input += n;
			continue ;
		}
		if (t_lstnew_add_back(&lst, input, n, type) == FAILURE)
			return (clear_and_fatal_exit(&lst, info));
		input += n;
	}
	return (lst);
}
