/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_judge.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:23:53 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/05 04:26:07 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static bool	is_doubled_op(const char *s)
{
	return (s[0] && s[0] == s[1] && ft_strchr("&|<>", s[0]));
}

t_token_type	what_type(int state)
{
	if (state == STATE_SQUOTE)
		return (SUB_TOKEN_SQUOTE);
	if (state == STATE_DQUOTE)
		return (SUB_TOKEN_DQUOTE);
	if (state == STATE_DOLLER)
		return (SUB_TOKEN_GENERAL);
	if (state == STATE_DOLLER_DQUOTE)
		return (SUB_TOKEN_DQUOTE);
	return (SUB_TOKEN_GENERAL);
}

bool	is_env_delimiter(int c)
{
	if (c == '_' || ft_isalnum(c))
		return (false);
	return (true);
}

int	operator_len(char *input)
{
	if (is_doubled_op(input))
		return (2);
	return (1);
}

t_token_type	str_type(char *input)
{
	if (is_doubled_op(input))
	{
		if (input[0] == '<')
			return (TOKEN_HEREDOC);
		if (input[0] == '>')
			return (TOKEN_APPEND);
		if (input[0] == '|')
			return (TOKEN_DISJUNCTIONE);
		return (TOKEN_CONJUNCTIONE);
	}
	if (input[0] && ft_strchr(OPERATOR, input[0]))
		return ((t_token_type)input[0]);
	if (input[0] && ft_strchr(DELIMITER, input[0]))
		return (TOKEN_SPACE);
	return (TOKEN_WORD);
}
