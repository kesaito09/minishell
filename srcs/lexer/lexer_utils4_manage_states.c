/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils4_manage_states.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:11:31 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/02 20:12:58 by kesaitou         ###   ########.fr       */
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

int			manage_sub_token(t_token **token_list, char **input, t_clist **c_list, t_state_tab *state)
{
	if (state ->s_sub == SUB_TOKEN_DOLLAR && is_delimiter_variables(**input))
	{
		if (commit_token(token_list, c_list, SUB_TOKEN_DOLLAR) == FAILUER)
			return (FAILUER);
	}
	if (**input == '$')
		state ->s_sub = SUB_TOKEN_DOLLAR;
	return (SUCCESS);
}

static int	manage_state_general(t_token **token_list, char **input,
		t_clist **c_list, t_state_tab *state)
{
	if (can_be_splitted(*input))
	{
		if (*c_list)
		{
			if (add_commit_token(token_list, &((*c_list) ->token_clist) , TOKEN_WORD) == FAILUER)
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
		if (state ->s_sub == SUB_TOKEN_DOLLAR)
			state ->s_sub = SUB_TOKEN_GENERAL;	
	}
	else
	{
		if (manage_sub_token(token_list, input, c_list, state) == FAILUER)
			return (FAILUER);		
		if (manage_append_char(c_list, **input) == FAILUER)
			return (FAILUER);
		(*input)++;
	}
	return (SUCCESS);
}

static int	manage_state_quote(t_token	**token_list, char **input,
		t_clist **c_list)
{
	if (manage_append_char(c_list, **input) == FAILUER)
		return (FAILUER);
	(*input)++;
	(void)token_list;
	return (SUCCESS);
}

int	manage_state_transition(t_token **token_list, char **input, t_state_tab *state,
		t_clist **c_list)
{
	int	flag;
	int new;

	new = state_check(state ->s_main, input);
	if (state ->s_main != new)
	{
		/* code */
	}
	
	if (state ->s_main == STATE_GENERAL)
		flag = manage_state_general(token_list, input, c_list);
	else
		flag = manage_state_quote(token_list, input, c_list);
	if (flag == FAILUER)
		return (FAILUER);
	if (**input == '\0')
		return (commit_token(token_list, &((*c_list) ->token_clist) , TOKEN_WORD));
	return (SUCCESS);
	
}
