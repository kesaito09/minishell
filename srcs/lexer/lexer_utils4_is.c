/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils4_is.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:23:53 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/03 07:12:58 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

bool	is_operator(char *str)
{
	if (*str == '|' || *str == '<' || *str == '>' || *str == '(' || *str == ')')
		return (true);
	if (!ft_strncmp(str, "&&", 2))
		return (true);
	return (false);
}

bool	is_delimiter(int c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

bool	can_be_splitted(char *str)
{
	if (is_delimiter(*str))
		return (true);
	if (is_operator(str))
		return (true);
	if (!ft_strncmp(str, "&&", 2))
		return (true);
	return (false);
}

bool	is_sub_token(t_token_type type)
{
	if (type == SUB_TOKEN_GENERAL 
		|| type == SUB_TOKEN_SQUOTE 
		|| type == SUB_TOKEN_DQUOTE 
		|| type == SUB_TOKEN_DOLLAR)
		return (true);
	return (false);	
}

t_token_type	what_subtype(t_state_tab *state)
{
	if (state->s_main == STATE_SQUOTE)
		return (SUB_TOKEN_SQUOTE);
	if (state->s_main == STATE_DQUOTE)
		return (SUB_TOKEN_DQUOTE);
	return (SUB_TOKEN_GENERAL);
}
