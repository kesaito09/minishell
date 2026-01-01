/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils4_manage_states.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:11:31 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/01 09:16:32 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static int	state_check(int state, char **input, t_char_list **c_list)
{
	char	new_state;
	
	if (**input == STATE_SQUOTE || **input == STATE_DQUOTE)
	{
		if (state == **input)
		{
			if (append_char(c_list, **input) == FAILUER)
				return (FAILUER);
			(*input)++;
			new_state = STATE_GENERAL;
		}
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
		int *state, t_char_list **c_list)	
{
	if (append_char(c_list, **input) == FAILUER)
		return (FAILUER);
	if (**input == *state)
		*state = STATE_GENERAL;
	(*input)++;
	(void)token_list;
	return (SUCCESS);
}

int	manage_state_transition(t_token **token_list, char **input, int *state,
		t_char_list **c_list)
{	
	int	flag;
	int	new;
	
	new = state_check(*state, input, c_list);
	if (*state == STATE_GENERAL)
		flag = manage_state_general(token_list, input, c_list);
	else
		flag = manage_state_quote(token_list, input, state, c_list);
	if (flag == FAILUER)
		return (FAILUER);
	if (**input == '\0')
		return (add_commit_token(token_list, c_list, TOKEN_WORD));
	return (SUCCESS);
}
