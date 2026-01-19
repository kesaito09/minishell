/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_judge.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:23:53 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/19 07:50:28 by natakaha         ###   ########.fr       */
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
		return (SUB_TOKEN_DOLLAR);
	if (state == STATE_DOLLER_DQUOTE)
		return (SUB_TOKEN_DOLLAR_DQUOTE);
	return (SUB_TOKEN_GENERAL);
}

bool	is_env_delimiter(int c)
{
	if (c == '_' || ft_isalnum(c))
		return (false);
	return (true);
}

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
