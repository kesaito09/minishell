/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils5_manage_operaters.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:15:52 by kesaitou          #+#    #+#             */
/*   Updated: 2025/12/21 01:09:10 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static int	hundle_consective_op1(t_token **token_list, char **input, char *op)
{
	if (!ft_strncmp(*input, "<<", 2))
	{
		op = ft_strdup("<<");
		if (!op)
			return (FAILUER);
		add_token(token_list, op, TOKEN_HEREDOC);
		(*input) += 2;
	}
	else if (!ft_strncmp(*input, ">>", 2))
	{
		op = ft_strdup(">>");
		if (!op)
			return (FAILUER);
		add_token(token_list, op, TOKEN_APPEND);
		(*input) += 2;
	}
	return (SUCCESS);
}

static int	hundle_consective_op2(t_token **token_list, char **input, char *op)
{
	if (!ft_strncmp(*input, "||", 2))
	{
		op = ft_strdup("||");
		if (!op)
			return (FAILUER);
		add_token(token_list, op, TOKEN_DISJUNCTIONE);
		(*input) += 2;
	}
	else if (!ft_strncmp(*input, "&&", 2))
	{
		op = ft_strdup("&&");
		if (!op)
			return (FAILUER);
		add_token(token_list, op, TOKEN_CONJUNCTIONE);
		(*input) += 2;
	}
	return (SUCCESS);
}

static int	hundle_single_op1(t_token **token_list, char **input, char *op)
{
	if (!ft_strncmp(*input, "(", 1))
	{
		op = ft_strdup("(");
		if (!op)
			return (FAILUER);
		add_token(token_list, op, TOKEN_PARENTHESIS_LEFT);
		(*input)++;
	}
	else if (!ft_strncmp(*input, ")", 1))
	{
		op = ft_strdup(")");
		if (!op)
			return (FAILUER);
		add_token(token_list, op, TOKEN_PARENTHESIS_RIGHT);
		(*input)++;
	}
	else if (!ft_strncmp(*input, "|", 1))
	{
		op = ft_strdup("|");
		if (!op)
			return (FAILUER);
		add_token(token_list, op, TOKEN_PIPE);
		(*input)++;
	}
	return (SUCCESS);
}

static int	hundle_single_op2(t_token **token_list, char **input, char *op)
{
	if (!ft_strncmp(*input, ">", 1))
	{
		op = ft_strdup(">");
		if (!op)
			return (FAILUER);
		add_token(token_list, op, TOKEN_REDIRECT_OUT);
		(*input)++;
	}
	else if (!ft_strncmp(*input, "<", 1))
	{
		op = ft_strdup("<");
		if (!op)
			return (FAILUER);
		add_token(token_list, op, TOKEN_REDIRECT_IN);
		(*input)++;
	}
	return (SUCCESS);
}

int	manage_operater(t_token **token_list, char **input)
{
	char *op;

	op = NULL;
	if (hundle_consective_op1(token_list, input, op) == FAILUER)
		return (FAILUER);
	if (hundle_consective_op2(token_list, input, op) == FAILUER)
		return (FAILUER);
	if (hundle_single_op1(token_list, input, op) == FAILUER)
		return (FAILUER);
	if (hundle_single_op2(token_list, input, op) == FAILUER)
		return (FAILUER);
	return (SUCCESS);
}
