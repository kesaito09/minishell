/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2_manage_states.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:11:31 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/03 23:59:13 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int	state_check(int state, char **input)
{
	if (**input == STATE_SQUOTE || **input == STATE_DQUOTE)
	{
		if (state == **input)
			return (STATE_GENERAL);
		else if (state == STATE_GENERAL)
			return (**input);		
		else
			return (state);
	}
	return (state);
}

int	manage_sub_token(t_token **token_list, char **input,
		t_clist **c_list, t_state_tab *state)
{
	if ((state->s_sub == STATE_DOLLER || state ->s_sub == STATE_DOLLER_DQUOTE) && is_delimiter_variables(**input))
	{
		if (commit_subtoken_wrapper(token_list, c_list, what_type(state ->s_sub)) == FAILUER)
			return (FAILUER);		
		state->s_sub = state->s_main;
	}
	if (**input == '$' && state->s_main != STATE_SQUOTE)
	{
		if (state->s_sub != STATE_DOLLER && (*c_list)->sub_clist)
		{
			if (commit_subtoken_wrapper(token_list, c_list,
					what_type(state ->s_main)) == FAILUER)
				return (FAILUER);
		}
		if (state ->s_main == STATE_DQUOTE)
			state ->s_sub = STATE_DOLLER_DQUOTE;
		else		
			state->s_sub = STATE_DOLLER;
	}
	return (SUCCESS);
}


static int	manage_state_general(t_token **token_list, char **input,
		t_clist **c_list, t_state_tab *state)
{
	if (can_be_splitted(*input))
	{
		if ((*c_list) ->token_clist)
		{
			if (commit_word_token(token_list, c_list, state) == FAILUER)
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
		if (state->s_sub == STATE_DOLLER || state ->s_sub == STATE_DOLLER_DQUOTE)
			state->s_sub = STATE_GENERAL;
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
		t_clist **c_list, t_state_tab *state)
{
	if (**input == (char)state->s_main)
		return (SUCCESS);
	if (manage_sub_token(token_list, input, c_list, state) == FAILUER)
		return (FAILUER);	
	if (manage_append_char(c_list, **input) == FAILUER)
		return (FAILUER);
	(*input)++;
	return (SUCCESS);
}

int	hundle_quote(t_token **token_list, char **input,
		t_clist **c_list, t_state_tab *state)
{
	int	new;

	new = state_check(state->s_main, input);
	if ((**input != '\'' && **input != '"') || new == state->s_main)
		return (SUCCESS);
	if (state->s_sub == STATE_DOLLER || state ->s_sub == STATE_DOLLER_DQUOTE)
	{
		if (commit_subtoken_wrapper(token_list, c_list, what_type(state ->s_sub)) == FAILUER)
			return (FAILUER);
		state->s_sub = state->s_main;
	}
	if (commit_subtoken_wrapper(token_list, c_list, what_type(state ->s_main)) == FAILUER)
		return (FAILUER);
	state->s_main = new;
	state->s_sub = new;
	(*input)++;
	return (SUCCESS);
}

int	manage_state_transition(t_token **token_list, char **input,
		t_state_tab *state, t_clist **c_list)
{
	int	flag;

	if (hundle_quote(token_list, input, c_list, state) == FAILUER)
		return (FAILUER);
	if (state->s_main == STATE_GENERAL)
		flag = manage_state_general(token_list, input, c_list, state);
	else
		flag = manage_state_quote(token_list, input, c_list, state);
	if (flag == FAILUER)
		return (FAILUER);
	if (**input == '\0' && (*c_list)->token_clist)
		return (commit_word_token(token_list, c_list, state));
	return (SUCCESS);
}

