/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer4_subtoken.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 06:22:25 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/04 00:03:10 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int	attach_sub_tokens(t_token **token_list, t_clist **c_list)
{
	t_token	*last_token;

	last_token = t_lstlast(*token_list);
	if (!last_token)
		return (FAILUER);
	last_token->sub_token = (*c_list)->sub_tokens;
	(*c_list)->sub_tokens = NULL;
	return (SUCCESS);
}

int	commit_token(t_token **token_list, t_clist **c_list, t_token_type type)
{
	char	*token;

	token = NULL;
	if (is_sub_token(type) && (*c_list) ->sub_clist)
	{
		token = list_to_string(&((*c_list) ->sub_clist));
		if (!token)
			return (FAILUER);
		if (!*token)
			return (SUCCESS);
		add_token(&((*c_list) ->sub_tokens), token, type);
	}
	if (type == TOKEN_WORD && (*c_list) ->token_clist)
	{
		token = list_to_string(&((*c_list) ->token_clist));
		if (!token)
			return (FAILUER);
		if (add_token(token_list, token, type) == FAILUER)
			return (FAILUER);
	}
	return (SUCCESS);
}

int	commit_subtoken_wrapper(t_token **token_list,
		t_clist **c_list, t_token_type type)
{
	if (!((*c_list)->sub_clist))
		return (SUCCESS);
	return (commit_token(token_list, c_list, type));
}

int	commit_word_token(t_token **token_list, t_clist **c_list,
		t_state_tab *state)
{
	if (state->s_sub == STATE_DOLLER || state ->s_sub == STATE_DOLLER_DQUOTE)
	{
		if (commit_subtoken_wrapper(token_list, c_list, what_type(state ->s_sub)) == FAILUER)
			return (FAILUER);
		state->s_sub = state->s_main;
	}
	if (commit_token(token_list, c_list, TOKEN_WORD) == FAILUER)
		return (FAILUER);
	if (attach_sub_tokens(token_list, c_list) == FAILUER)
		return (FAILUER);
	state->s_sub = STATE_GENERAL;
	return (SUCCESS);
}



