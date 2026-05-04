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

bool	is_delimiter(int c)
{
	return (c == ' ' || c == '\n' || c == '\t');
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
	if (input[0] && ft_strchr("|&<>", input[0]) && input[0] == input[1])
		return (2);
	return (1);
}

int	str_type(char *op)
{
	if (op[0] && ft_strchr("&|<>", op[0]) && op[0] == op[1])
		return ((op[0] + 128));
	if (op[0] && ft_strchr("|<>()", op[0]))
		return (op[0]);
	if (op[0] && ft_strchr(" \t\n", op[0]))
		return (TOKEN_SPACE);
	return (TOKEN_WORD);
}
