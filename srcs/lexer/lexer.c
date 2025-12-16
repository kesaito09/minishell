/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:22:47 by kesaitou          #+#    #+#             */
/*   Updated: 2025/12/16 21:31:00 by kesaitou         ###   ########.fr       */
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

void	tokenizer(char *input, t_token **token_list)
{
	t_state		state;
	char		*op;
	t_char_list	*c_list;
	int			balance;

	state = STATE_GENERAL;
	c_list = NULL;
	balance = 0;
	while (*input)
	{
		if (state == STATE_GENERAL)
		{
			if (*input == '\'')
			{
				state = STATE_SQUOTE;
				append_char(&c_list, *input);
				input++;
			}
			else if (*input == '"')
			{
				state = STATE_DQUOTE;
				append_char(&c_list, *input);
				input++;
			}
			else if (is_delimiter(*input) || is_operator(*input) || !ft_strncmp(input, "&&", 2))
			{
				if (c_list)
				{
					add_token(token_list, list_to_string(&c_list), TOKEN_WORD);
					c_list = NULL;
				}
				if (is_operator(*input) || !ft_strncmp(input, "&&", 2))
				{
					if (!ft_strncmp(input, "<<", 2))
					{
						op = ft_strdup("<<");
						if (!op)
							return ;
						add_token(token_list, op, TOKEN_HEREDOC);
						input += 2;
						continue ;
					}
					else if (!ft_strncmp(input, ">>", 2))
					{
						op = ft_strdup(">>");
						if (!op)
							return ;
						add_token(token_list, op, TOKEN_APPEND);
						input += 2;
						continue ; // 一時的に例外処理にしてる後で直す
					}
					
					else if (!ft_strncmp(input, "||", 2))
					{
						op = ft_strdup("||");
						if (!op)
							return ;
						add_token(token_list, op, TOKEN_DISJUNCTIONE);
						input += 2;
						continue;
					}
					else if (!ft_strncmp(input, "&&", 2))
					{
						op = ft_strdup("&&");
						if (!op)
							return ;
						add_token(token_list, op, TOKEN_CONJUNCTIONE);
						input += 2;
						continue;
					}
					else if(!ft_strcmp(input, "("))
					{
						op = ft_strdup("(");
						if (!op)
							return ;
						add_token(token_list, op, TOKEN_PARENTHESIS_LEFT);
					}
					else if(!ft_strcmp(input, ")"))
					{
						op = ft_strdup(")");
						if (!op)
							return ;
						add_token(token_list, op, TOKEN_PARENTHESIS_RIGHT);
					}
					else if (!ft_strncmp(input, "|", 1))
					{
						op = ft_strdup("|");
						if (!op)
							return ;
						add_token(token_list, op, TOKEN_PIPE);
					}
					else if (!ft_strncmp(input, ">", 1))
					{
						op = ft_strdup(">");
						if (!op)
							return ;
						add_token(token_list, op, TOKEN_REDIRECT_OUT);
					}
					else if (!ft_strncmp(input, "<", 1))
					{
						op = ft_strdup("<");
						if (!op)
							return ;
						add_token(token_list, op, TOKEN_REDIRECT_IN);
					}
					input++;
				}
				else
					input++;
			}
			else if (*input == '\\')
			{
				input++;
				if (*input)
				{
					append_char(&c_list, *input);
					input++;
				}
			}
			else
			{
				append_char(&c_list, *input);
				input++;
			}
		}
		else if (state == STATE_SQUOTE)
		{
			if (*input == '\'')
			{
				state = STATE_GENERAL;
				append_char(&c_list, *input);
				input++;
			}
			else
			{
				append_char(&c_list, *input);
				input++;
			}
		}
		else if (state == STATE_DQUOTE)
		{
			if (*input == '"')
			{
				state = STATE_GENERAL;
				append_char(&c_list, *input);
				input++;
			}
			else
			{
				append_char(&c_list, *input);
				input++;
			}
		}
	}
	if (c_list)
	{
		add_token(token_list, list_to_string(&c_list), TOKEN_WORD);
		c_list = NULL;
	}
}

void	lexer(char *input, t_token **token_list)
{
	t_token	*last_node;
	t_token	*eof_node;

	tokenizer(input, token_list);
	if (!*token_list)
		return ;
	last_node = t_lstlast(*token_list);
	eof_node = t_lstnew(NULL);
	if (!eof_node)
		return ;
	eof_node->type = TOKEN_EOF;
	last_node->next = eof_node;
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
