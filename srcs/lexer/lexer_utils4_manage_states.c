/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils5_manage_states.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:11:31 by kesaitou          #+#    #+#             */
/*   Updated: 2025/12/19 16:14:22 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static int	manage_state_general(t_token **token_list, char **input,
		t_state *state, t_char_list **c_list)
{
	manage_quote(input, state, *c_list);
	if (is_delimiter(**input) || is_operator(**input) || !ft_strncmp(*input,
			"&&", 2))
	{
		if (*c_list)
		{
			add_token(token_list, list_to_string(c_list), TOKEN_WORD);
			*c_list = NULL;
		}
		if (is_operator(**input) || !ft_strncmp(*input, "&&", 2))
		{
			if (manage_operater(token_list, input) == FAILUER)
				return (FAILUER); // malloc失敗だけ
		}
		else
			(*input)++;
	}
	else
	{
		append_char(c_list, **input);
		(*input)++;
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
