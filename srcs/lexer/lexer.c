/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:22:47 by kesaitou          #+#    #+#             */
/*   Updated: 2025/12/19 15:56:51 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static int	is_operator(int c)
{
	return (c == '|' || c == '<' || c == '>' || c == '(' || c == ')');
}

static int	is_delimiter(int c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

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
	char	*op;

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

static void	manage_quote(char **input, t_state *state, t_char_list *c_list)
{
	if (**input == '\'')
	{
		*state = STATE_SQUOTE;
		append_char(&c_list, **input);
		(*input)++;
	}
	else if (**input == '"')
	{
		*state = STATE_DQUOTE;
		append_char(&c_list, **input);
		(*input)++;
	}
}

int	manage_state_general(t_token **token_list, char **input, t_state *state,
		t_char_list **c_list)
{
	manage_quote(input, state, *c_list);
	if (is_delimiter(**input) || is_operator(**input) || !ft_strncmp(*input,
			"&&", 2))
	{
		if (*c_list)
		{
			add_token(token_list, list_to_string(c_list), TOKEN_WORD);
			*c_list = NULL;
		}
		if (is_operator(**input) || !ft_strncmp(*input, "&&", 2))
		{
			if (manage_operater(token_list, input) == FAILUER)
				return (FAILUER); // malloc失敗だけ
		}
		else
			(*input)++;
	}
	else
	{
		append_char(c_list, **input);
		(*input)++;
	}
	return (SUCCESS);
}

int	manage_state_squote(char **input, t_state *state, t_char_list **c_list)
{
	if (**input == '\'')
	{
		*state = STATE_GENERAL;
		if (append_char(c_list, **input) == FAILUER)
			return (FAILUER);
		(*input)++;
	}
	else
	{
		if (append_char(c_list, **input) == FAILUER)
			return (FAILUER);
		(*input)++;
	}
	return (SUCCESS);
}

int	manage_state_dquote(char **input, t_state *state, t_char_list **c_list)
{
	if (**input == '"')
	{
		*state = STATE_GENERAL;
		if (append_char(c_list, **input) == FAILUER)
			return (FAILUER);
		(*input)++;
	}
	else
	{
		if (append_char(c_list, **input) == FAILUER)
			return (FAILUER);
		(*input)++;
	}
	return (SUCCESS);
}

int	manage_state_transition(t_token **token_list, char **input, t_state *state,
		t_char_list **c_list)
{
	if (*state == STATE_GENERAL)
	{
		if (manage_state_general(token_list, input, state, c_list) == FAILUER)
			return (FAILUER);
	}
	else if (*state == STATE_SQUOTE)
	{
		if (manage_state_squote(input, state, c_list) == FAILUER)
			return (FAILUER);
	}
	else if (*state == STATE_DQUOTE)
	{
		if (manage_state_dquote(input, state, c_list) == FAILUER)
			return (FAILUER);
	}
	return (SUCCESS);
}

int	tokenizer(char *input, t_token **token_list)
{
	t_state		state;
	t_char_list	*c_list;

	state = STATE_GENERAL;
	c_list = NULL;
	while (*input)
	{
		if (manage_state_transition(token_list, &input, &state,
				&c_list) == FAILUER)
			return (FAILUER);
	}
	if (state == STATE_SQUOTE || state == STATE_DQUOTE)
	{
		if (c_list)
			c_lstclear(&c_list, free);
		t_lstclear(token_list, free);
		ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
		return (FAILUER);
	}
	if (c_list)
	{
		add_token(token_list, list_to_string(&c_list), TOKEN_WORD);
		c_list = NULL;
	}
	return (SUCCESS);
}

int	lexer(char *input, t_token **token_list)
{
	t_token	*last_node;
	t_token	*eof_node;

	if (tokenizer(input, token_list) == FAILUER)
		return (FAILUER);
	if (!*token_list)
		return (FAILUER);
	last_node = t_lstlast(*token_list);
	eof_node = t_lstnew(NULL);
	if (!eof_node)
		return (FAILUER);
	eof_node->type = TOKEN_EOF;
	last_node->next = eof_node;
	return (SUCCESS);
}

// int	main(void)
// {
// 	t_token	*token;
// 	char	*test1;
// 	char	*test2;
// 	char	*test3;
// 	char	*test4;
// 	// char	*test5;

// 	t_token	*token2;
// 	t_token	*token3;
// 	t_token	*token4;
// 	// t_token	*token5;

// 	token = NULL;
// 	test1 = " cat- e  file1 file2 file3 infile || cat -e";
// 	test2 = "cat -e  file1 file2 file3 infila && echo aa";
// 	test3 = "awk '{print $1}'";
// 	test4 = "echo \"$USER\" \'$USER\'";
// 	printf("%s\n", test1);
// 	my_lex(test1, &token);
// 	while (token)
// 	{
// 		printf(" WORD %s : TYPE ", token->token);
// 		printf("%u\n", token->type);
// 		token = token->next;
// 	}
// 	token2 = NULL;
// 	my_lex(test2, &token2);
// 	printf("%s\n", test2);
// 	while (token2)
// 	{
// 		printf(" WORD %s : TYPE ", token2->token);
// 		printf("%u\n", token2->type);
// 		token2 = token2->next;
// 	}
// 	token3 = NULL;
// 	my_lex(test3, &token3);
// 	printf("%s\n", test3);
// 	while (token3)
// 	{
// 		printf(" WORD %s : TYPE ", token3->token);
// 		printf("%u\n", token3->type);
// 		token3 = token3->next;
// 	}
// 	token4 = NULL;
// 	my_lex(test4, &token4);
// 	printf("%s\n", test4);
// 	while (token4)
// 	{
// 		printf(" WORD %s : TYPE ", token4->token);
// 		printf("%u\n", token4->type);
// 		token4 = token4->next;
// 	}
// }

/*
memo
	inputがヌルになるまでループして、状態によって分岐させる
	3状態の分岐を作ってcontinueで制御する



	[

		ls       -l    -a

		echo     hello

		ls|grep

		cat<infile>>outfile

		echo 'hello      world'

		echo "ls | cat"

		echo "'hello'"

		echo ""

		abc'def'"ghi"

		echo "$USER" '$USER'

		awk '{print $1}'
							]



	}


*/
