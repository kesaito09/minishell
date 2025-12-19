/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils4_manage_states.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:11:31 by kesaitou          #+#    #+#             */
/*   Updated: 2025/12/20 05:48:19 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static void	manage_quote(char **input, t_state *state, t_char_list *c_list)
{
	if (**input == '\'')
	{
		*state = STATE_SQUOTE;
		append_char(&c_list, **input);
		(*input)++;
	}
	else if (**input == '"')
	{
		*state = STATE_DQUOTE;
		append_char(&c_list, **input);
		(*input)++;
	}
}

static int	manage_state_general(t_token **token_list, char **input,
		t_state *state, t_char_list **c_list)
{
	manage_quote(input, state, *c_list);
	if (is_delimiter(**input) || is_operator(**input) || !ft_strncmp(*input,
			"&&", 2))
	{
		if (*c_list)
			if (add_token(token_list, list_to_string(c_list), TOKEN_WORD) == FAILUER)
				return (FAILUER);
		if (is_operator(**input) || !ft_strncmp(*input, "&&", 2))
			if (manage_operater(token_list, input) == FAILUER)
				return (FAILUER);
		if (is_delimiter(**input))
			(*input)++;
	}
	else
	{
		append_char(c_list, **input);
		(*input)++;
		if (**input == '\0')
			if (add_token(token_list, list_to_string(c_list), TOKEN_WORD) == FAILUER)
				return (FAILUER);
	}
	return (SUCCESS);
}

static int	manage_state_squote(char **input, t_state *state,
		t_char_list **c_list)
{
	if (**input == '\'')
	{
		*state = STATE_GENERAL;
		if (append_char(c_list, **input) == FAILUER)
			return (FAILUER);
		(*input)++;
	}
	else
	{
		if (append_char(c_list, **input) == FAILUER)
			return (FAILUER);
		(*input)++;
	}
	return (SUCCESS);
}

static int	manage_state_dquote(char **input, t_state *state,
		t_char_list **c_list)
{
	if (**input == '"')
	{
		*state = STATE_GENERAL;
		if (append_char(c_list, **input) == FAILUER)
			return (FAILUER);
		(*input)++;
	}
	else
	{
		if (append_char(c_list, **input) == FAILUER)
			return (FAILUER);
		(*input)++;
	}
	return (SUCCESS);
}

int	manage_state_transition(t_token **token_list, char **input, t_state *state,
		t_char_list **c_list)
{
	if (*state == STATE_GENERAL)
	{
		if (manage_state_general(token_list, input, state, c_list) == FAILUER)
			return (FAILUER);
	}
	else if (*state == STATE_SQUOTE)
	{
		if (manage_state_squote(input, state, c_list) == FAILUER)
			return (FAILUER);
	}
	else if (*state == STATE_DQUOTE)
	{
		if (manage_state_dquote(input, state, c_list) == FAILUER)
			return (FAILUER);
	}
	return (SUCCESS);
}
