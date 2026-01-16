/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:22:47 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/16 12:29:52 by natakaha         ###   ########.fr       */
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

int	str_type(char *op)
{
	if (ft_strchr("&|<>", op[0]) && op[0] == op[1])
		return ((op[0] + 128));
	else if (ft_strchr("|<>()", op[0]))
		return (op[0]);
	else
		return (TOKEN_WORD);
}

int	input_len(char *input, char *charset)
{
	int	len;

	len = 0;
	if (!input)
		return (-1);
	while (input[len])
	{
		if (ft_strchr(charset, input[len]))
			return (len);
		len++;
	}
	return (len);
}

int	token_len(char *input, char *charset)
{
	int	len;
	int	tmp;

	if (!input)
		return (-1);
	len = input_len(input, charset);
	tmp = strchr_len(input, '&');
	if (input[tmp + 1] == '&' && tmp < len && tmp >= 0)
		len = tmp;
	return (len);
}

int	logical_len(char *input)
{
	if (ft_strchr("|&<>", input[0]) && input[0] == input[1])
		return (2);
	return (1);
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

char	*manage_state_general(char **input)
{
	int		n;
	char	*str;
	t_token	*node;

	if (!*input)
		return (NULL);
	n = token_len(*input, "'\" \t\n|()<>");
	if (n == 0 && ft_strchr(" \t\n", *input))
	{
		*input++;
		return (NULL);
	}
	else if (n == 0 && ft_strchr("'\"", *input))
		return (NULL);
	else if (n == 0)
		n = logical_len(*input);
	str = ft_strndup(*input, n);
	input += n;
	return (str);
}

char	*manage_state_quote(char **input, t_state state)
{
	int		n;
	char	*str;
	t_token	*node;

	*input++;
	n = strchr_len(*input, state);
	if (n == -1)
	{
		ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
		return (NULL);
	}
	str = ft_strndup(input + 1, n - 1);
	*input += n;
	return (str);
}

char	*make_str(char **input)
{
	char	*lst;
	char	*trash;
	char	*new;

	lst = ft_strdup("");
	if (!lst)
		return (NULL);
	while (**input)
	{
		if (ft_strchr("'\"", **input))
			new = manage_state_quote(input, **input);
		else
			new = manage_state_general(input);
		if (!new)
			return (free(lst), NULL);
		trash = lst;
		lst = ft_strjoin(trash, new);
		free(trash);
		free(new);
		if (!lst)
			return (NULL);
		if (ft_strchr(" \t\n\0", **input) && str_type(*input) != TOKEN_WORD)
			return (lst);
	}
}

t_token	*manage_state_transition(char *input)
{
	t_state	state;
	t_state	*new;
	t_state	*lst;
	int		n;

	state = state_check(state, *input);
	lst = NULL;
	new = NULL;
	while (input)
	{
		if (state == STATE_GENERAL)
			new = manage_state_general(&input);
		else if (state == STATE_DQUOTE || state == STATE_SQUOTE)
			new = manage_state_quote(&input, state);
		if (!new)
			return (NULL);
		t_lstadd_back(&lst, new);
	}
	return (lst);
}

t_token	*tokenizer(char *input)
{
	t_state	state;

	if (!input)
		return (NULL);
	state = manage_state_transition(input);
	if (state == STATE_SQUOTE || state == STATE_DQUOTE)
	{

		return (NULL);
	}
	return (lst);
}
