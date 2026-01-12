/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2_manage_states.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:11:31 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/12 10:21:26 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

bool	is_dollar_sub(int s_sub)
{
	return (s_sub == STATE_DOLLER || s_sub == STATE_DOLLER_DQUOTE);
}

static void	begin_dollar(t_state_tab *state)
{
	if (state->s_main == STATE_DQUOTE)
		state->s_sub = STATE_DOLLER_DQUOTE;
	else
		state->s_sub = STATE_DOLLER;
}

int	commit_sub_and_set(t_lexer *lx, int sub_state, int next)
{
	if (commit_subtoken_wrapper(&(lx->token_list), &lx->buf,
			what_type(sub_state)) == FAILUER)
		return (FAILUER);
	lx->state->s_sub = next;
	return (SUCCESS);
}

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


static int	start_dollar_if_qmark(t_lexer *lx, int ch)
{
	int	next;

	if (ch != '$')
		return (SUCCESS);
	if (lx->state->s_main == STATE_SQUOTE)
		return (SUCCESS);

	next = (*lx->input)[1];
	if (next != '?')
		return (SUCCESS);
	if (!is_dollar_sub(lx->state->s_sub) && lx->buf->sub_clist)
	{
		if (commit_subtoken_wrapper(&(lx->token_list), &lx->buf,
				what_type(lx->state->s_main)) == FAILUER)
			return (FAILUER);
	}
	begin_dollar(lx->state);
	return (SUCCESS);
}

static int	consume_char(t_lexer *lx)
{
	int	ch;

	ch = **lx->input;

	if (start_dollar_if_qmark(lx, ch) == FAILUER)
		return (FAILUER);

	if (manage_append_char(&lx->buf, ch) == FAILUER)
		return (FAILUER);
	if (is_dollar_sub(lx->state->s_sub) && ch == '?')
	{
		if (commit_sub_and_set(lx, lx->state->s_sub, lx->state->s_main) == FAILUER)
			return (FAILUER);
	}
	(*lx->input)++;
	return (SUCCESS);
}

static int	token_split_in_general(t_lexer *lx)
{
	if (lx->buf->token_clist)
	{
		if (commit_word_token(&(lx->token_list), &lx->buf, lx->state) == FAILUER)
			return (FAILUER);
	}
	if (is_operator(*lx->input))
	{
		if (manage_operater(&(lx->token_list), lx->input) == FAILUER)
			return (FAILUER);
		else if (is_delimiter(**lx->input))
			(*lx->input)++;
	}
	else
		(*lx->input)++;

	if (is_dollar_sub(lx->state->s_sub))
		lx->state->s_sub = STATE_GENERAL;

	return (SUCCESS);
}

static int	manage_state_general(t_lexer *lex)
{
	if (can_be_splitted(*lex->input))
		return (token_split_in_general(lex));
	return (consume_char(lex));
}

static int	manage_state_quote(t_lexer *lex)
{
	return (consume_char(lex));
}

int	switch_main_state(t_lexer *lx, int new_main)
{
	if (!lx || !lx->state || !lx->input)
		return (FAILUER);

	lx->state->s_main = new_main;
	if (is_dollar_sub(lx->state->s_sub))
		lx->state->s_sub = lx->state->s_main;

	(*lx->input)++;
	return (SUCCESS);
}

int	hundle_quote(t_lexer *lex)
{
	int	new;

	new = state_check(lex->state->s_main, lex->input);
	if ((**lex->input != '\'' && **lex->input != '"') || new == lex->state->s_main)
		return (SUCCESS);
	return (switch_main_state(lex, new));
}
int	manage_state_transition(t_lexer *lex)
{
	int	flag;

	if (hundle_quote(lex) == FAILUER)
		return (FAILUER);

	if (lex->state->s_main == STATE_GENERAL)
		flag = manage_state_general(lex);
	else
		flag = manage_state_quote(lex);

	return (flag);
}
