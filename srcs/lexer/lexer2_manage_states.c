/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2_manage_states.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:11:31 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/16 01:49:13 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

// bool	is_dollar_sub(int s_sub)
// {
// 	return (s_sub == STATE_DOLLER || s_sub == STATE_DOLLER_DQUOTE);
// }

//$が始まるときのじょうたいを更新するやつ
static void	begin_dollar(t_state_tab *state)
{
	if (state->s_main == STATE_DQUOTE)
		state->s_sub = STATE_DOLLER_DQUOTE;
	else
		state->s_sub = STATE_DOLLER;
}

int	commit_sub_and_set(t_lexer *lex, int sub_state, int next)
{
	if (commit_clist(&(lex->token_list), &lex->buf,
			what_type(sub_state)) == FAILUER)
		return (FAILUER);
	lex->state->s_sub = next;
	return (SUCCESS);
}

int	state_check(char c, int state)
{
	if (c == '\'' || c == '"' || c == '$')
	{
		if ((c == '\'' || c == '"') && state == c)
			return (STATE_GENERAL);
		else if (state == STATE_GENERAL)
			return (c);
		else if (state == STATE_DQUOTE && c == '$')
			return (STATE_DOLLER_DQUOTE);
		else
			return (state);
	}
	return (state);
}


static int	start_dollar(t_lexer *lex, int ch)
{
	if (lex->state->s_main == STATE_SQUOTE)
		return (SUCCESS);
	if (lex->buf->sub_clist)
	{
		if (commit_clist(&(lex->token_list), &lex->buf,
				what_type(lex->state->s_main)) == FAILUER)
			return (FAILUER);
	}
	begin_dollar(lex->state);
	return (SUCCESS);
}

static int	consume_char(t_lexer *lex)
{
	int		ch;
	int		next;

	ch = *lex->input;
	if (ch == '$')
	{
		if (start_dollar(lex, ch) == FAILUER)
			return (FAILUER);
		next = lex->input[1];
			if (ch == '?')
			{
				if (commit_sub_and_set(lex, lex->state->s_sub, lex->state->s_main) == FAILUER)
				return (FAILUER);
			}
			else
			{
				if (next == '\0' || is_delimiter_variables(next))
				{
					if (commit_sub_and_set(lex, lex->state->s_sub, lex->state->s_main) == FAILUER)
					return (FAILUER);
				}
			}
	}
	if (append_char(&lex->buf, ch) == FAILUER)
		return (FAILUER);
	(*lex->input)++;
	return (SUCCESS);
}

static int	token_split_in_general(t_lexer *lex)
{
	if (lex->buf->token_clist)
	{
		if (commit_word_token(&(lex->token_list), &lex->buf, lex->state) == FAILUER)
			return (FAILUER);
	}
	if (is_operator(*lex->input))
	{
		if (manage_operater(&(lex->token_list), lex->input) == FAILUER)
			return (FAILUER);
		else if (is_delimiter(*lex->input))
			(*lex->input)++;
	}
	else
		(*lex->input)++;
	if (lex->state->s_sub == STATE_DOLLER || lex->state->s_sub == STATE_DOLLER_DQUOTE)
		lex->state->s_sub = STATE_GENERAL;
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

// int	switch_main_state(t_lexer *lex, int new)
// {
// 	if (!lex || !lex->state || !lex->input)
// 		return (FAILUER);

// 	lex->state->s_main = new;
// 	if (lex->state->s_sub == STATE_DOLLER || lex->state->s_sub == STATE_DOLLER_DQUOTE)
// 		lex->state->s_sub = lex->state->s_main;
// 	(*lex->input)++;
// 	return (SUCCESS);
// }

int	is_state_change(char c, t_state state)
{
	t_state	new;

	new = (t_state)state_check(c, state);
	if (state != new)
		return (true);
	return (false);
}

int	manage_state_transition(char *input, t_token **t_lst, t_token **s_list, t_state state)
{
	int	flag;

	if (is_state_change(*input, state))
		commit_clist(s_list, state);
	if (lex->state->s_main == STATE_GENERAL)
		flag = manage_state_general(lex);
	else
		flag = manage_state_quote(lex);
	return (flag);
}
