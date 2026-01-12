/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:22:47 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/12 09:50:12 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"


void	init_state(t_state_tab *state)
{
	state->s_main = STATE_GENERAL;
	state->s_sub = STATE_GENERAL;
}

static void	lexer_builder_clear(t_lexer_builder **buf)
{
	if (!buf || !*buf)
		return ;
	if ((*buf)->token_clist)
		c_lstclear(&((*buf)->token_clist), free);
	if ((*buf)->sub_clist)
		c_lstclear(&((*buf)->sub_clist), free);
	if ((*buf)->sub_tokens)
		t_lstclear(&((*buf)->sub_tokens), free);
	free(*buf);
	*buf = NULL;
}

static void	lexer_destroy(t_lexer *lex, bool free_tokens)
{
	if (!lex)
		return ;

	lexer_builder_clear(&lex->buf);
	if (free_tokens && lex->token_list)
	{
		t_lstclear(&(lex->token_list), free);
		lex->token_list = NULL;
	}
	lex->input = NULL;
	lex->state = NULL;
}

static int	lexer_init(t_lexer *lex, char **input, t_state_tab *state)
{
	if (!lex || !input || !state)
		return (FAILUER);

	lex->token_list = NULL;
	lex->input = input;
	lex->state = state;
	init_state(lex->state);
	lex->buf = ft_calloc(1, sizeof(*lex->buf));
	if (!lex->buf)
		return (FAILUER);
	return (SUCCESS);
}

static int	lexer_flush_end(t_lexer *lx)
{
	if (is_dollar_sub(lx->state->s_sub))
	{
		if (commit_sub_and_set(lx, lx->state->s_sub, lx->state->s_main) == FAILUER)
			return (FAILUER);
	}

	if (lx->buf->token_clist)
	{
		if (commit_word_token(&(lx->token_list), &lx->buf, lx->state) == FAILUER)
			return (FAILUER);
	}
	return (SUCCESS);
}

t_token	*tokenizer(char *input)
{
	t_lexer		lex;
	t_state_tab	state;
	char		*p;

	if (!input)
		return (NULL);
	p = input;

	if (lexer_init(&lex, &p, &state) == FAILUER)
		return (NULL);

	while (**lex.input)
	{
		if (manage_state_transition(&lex) == FAILUER)
		{
			lexer_destroy(&lex, true);
			return (NULL);
		}
	}

	if (lexer_flush_end(&lex) == FAILUER)
	{
		lexer_destroy(&lex, true);
		return (NULL);
	}

	if (lex.state->s_main == STATE_SQUOTE || lex.state->s_main == STATE_DQUOTE)
	{
		lexer_destroy(&lex, true);
		ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
		return (NULL);
	}

	lexer_destroy(&lex, false);
	return (lex.token_list);
}
