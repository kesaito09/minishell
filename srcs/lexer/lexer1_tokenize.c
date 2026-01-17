/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:22:47 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/17 17:23:17 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int	logical_len(char *input)
{
	if (ft_strchr("|&<>", input[0]) && input[0] == input[1])
		return (2);
	return (1);
}

int	str_type(char *op)
{
	if (ft_strchr("&|<>", op[0]) && op[0] == op[1])
		return ((op[0] + 128));
	else if (ft_strchr("|<>()", op[0]))
		return (op[0]);
	else if (ft_strchr(" \t\n", op[0]))
		return (TOKEN_SPACE);
	else
		return (TOKEN_WORD);
}

int	word_len(char *input, char *charsplit, char *charignore)
{
	int	len;
	int	tmp;

	len = 0;
	if (!input)
		return (-1);
	while (input[len])
	{
		if ((ft_strchr(charsplit, input[len]))
			|| (charignore && input[len] == '&' && input[len + 1] == '&'))
			return (len);
		if (ft_strchr(charignore, input[len]))
		{
			tmp = strchr_len(input + len + 1, input[len]) + 1;
			if (!tmp)
			{
				ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
				return (-1);
			}
			len += tmp + 1;
		}
		else
			len++;
	}
	return (len);
}

t_token	*tokenizer(char *input)
{
	t_token			*lst;
	t_token			*new;
	t_token_type	type;
	int				n;

	lst = NULL;
	while (*input)
	{
		type = (t_token_type)str_type(input);
		if (type == TOKEN_WORD)
			n = word_len(input, SPLIT, QUOTE);
		else if (type == TOKEN_SPACE && input++)
			continue ;
		else
			n = logical_len(input);
		new = t_lstnew(ft_strndup(input, n), free);
		if (!new)
			return (t_lstclear(&lst, free), NULL);
		input += n;
		new->type = type;
		t_lstadd_back(&lst, new);
	}
	return (lst);
}
