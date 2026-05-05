/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2_scan.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 00:00:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/06 00:00:00 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

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
