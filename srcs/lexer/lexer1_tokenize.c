/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:22:47 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/16 01:19:09 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"


// void	init_state(t_state_tab *state)
// {
// 	state->s_main = STATE_GENERAL;
// 	state->s_sub = STATE_GENERAL;
// }

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

static t_lexer	lexer_init(char *input)
{
	t_lexer	lex;
	
	ft_bzero(&lex, sizeof(t_lexer));
	lex.input = input;
	lex.state->s_main = STATE_GENERAL;
	lex.state->s_sub = STATE_GENERAL;
	return (lex);
}

// static int	lexer_flush_end(t_lexer *lex)
// {
// 	if (lex->state->s_sub == STATE_DOLLER || lex->state->s_sub == STATE_DOLLER_DQUOTE)
// 	{
// 		if (commit_sub_and_set(lex, lex->state->s_sub, lex->state->s_main) == FAILUER)
// 			return (FAILUER);
// 	}
// 	if (lex->buf->token_clist)
// 	{
// 		if (commit_word_token(&(lex->token_list), &lex->buf, lex->state) == FAILUER)
// 			return (FAILUER);
// 	}
// 	return (SUCCESS);
// }

t_token	*tokenizer(char *input)
{
	t_state		state;
	t_token		*lst;
	
	if (!input)
		return (NULL);
	state = STATE_GENERAL;
	while (input)
	{
		state = manage_state_transition(input, &lst, state);
		if (state == FAILUER)
			return (t_lstclear(&lst, free), NULL);
	}
	if (state == STATE_SQUOTE || state == STATE_DQUOTE)
	{
		ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
		return (NULL);
	}
	return (lst);
}
