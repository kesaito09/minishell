/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils4_manage_states.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:11:31 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/02 15:14:00 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static int	state_check(int state, char **input)
{
	char		new_state;
	static int	flag = false;

	if (flag == true)
	{
		flag = false;
		state = STATE_GENERAL;
	}
	if (**input == STATE_SQUOTE || **input == STATE_DQUOTE)
	{
		if (state == **input)
			flag = true;
		else if (state == STATE_GENERAL)
			new_state = **input;
		else
			new_state = state;
		return (new_state);
	}
	return (state);
}

static int	manage_state_general(t_token **token_list, char **input,
		t_char_list **c_list)
{
	if (can_be_splitted(*input))
	{
		if (*c_list)
		{
			if (add_commit_token(token_list, c_list, TOKEN_WORD) == FAILUER)
				return (FAILUER);
		}
		if (is_operator(*input))
		{
			if (manage_operater(token_list, input) == FAILUER)
				return (FAILUER);
			else if (is_delimiter(**input))
				(*input)++;
		}
		else
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

static int	manage_state_quote(t_token	**token_list, char **input,
		t_char_list **c_list)
{
	if (append_char(c_list, **input) == FAILUER)
		return (FAILUER);
	(*input)++;
	(void)token_list;
	return (SUCCESS);
}

int	manage_state_transition(t_token **token_list, char **input, int *state,
		t_char_list **c_list)
{
	int	flag;

	*state = state_check(*state, input);
	if (*state == STATE_GENERAL)
		flag = manage_state_general(token_list, input, c_list);
	else
		flag = manage_state_quote(token_list, input, c_list);
	if (flag == FAILUER)
		return (FAILUER);
	if (**input == '\0')
		return (add_commit_token(token_list, c_list, TOKEN_WORD));
	return (SUCCESS);
}
