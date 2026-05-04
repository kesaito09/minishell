/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:22:47 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/05 05:50:46 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static void	*fatal_exit_wrapper(t_token **lst, t_shared_info *info)
{
	t_lstclear(lst, free);
	fatal_exit(info);
	return (NULL);
}

static int	quoted_span_len(const char *s)
{
	int	tail;

	tail = strchr_len((char *)s + 1, s[0]);
	if (tail < 0)
		return (-1);
	return (tail + 2);
}

int	shell_word_len(const char *input)
{
	int	i;
	int	span;

	i = 0;
	while (input[i])
	{
		if (ft_strchr(SPLIT, input[i])
			|| (input[i] == '&' && input[i + 1] == '&'))
			return (i);
		if (ft_strchr(QUOTE, input[i]))
		{
			span = quoted_span_len(input + i);
			if (span < 0)
				return (ft_putendl_fd(
						"minishell: syntax error: unclosed quote", 2),
					FAILURE);
			i += span;
		}
		else
			i++;
	}
	return (i);
}

int	scan_until(const char *s, const char *terminators)
{
	int	i;

	i = 0;
	while (s[i] && !ft_strchr(terminators, s[i]))
		i++;
	return (i);
}

t_token	*tokenizer(char *input, t_shared_info *info)
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
			n = shell_word_len(input);
		else if (type == TOKEN_SPACE && input++)
			continue ;
		else
			n = operator_len(input);
		if (n == FAILURE)
			return (t_lstclear(&lst, free), NULL);
		new = t_lstnew(ft_strndup(input, n), free);
		if (!new)
			return (fatal_exit_wrapper(&lst, info));
		input += n;
		new->type = type;
		t_lstadd_back(&lst, new);
	}
	return (lst);
}
