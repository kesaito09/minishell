/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:22:47 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/01 01:47:45 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_token	*tokenizer(char *input)
{
	t_state		state;
	t_char_list	*c_list;
	t_token		*token_list;

	state = STATE_GENERAL;
	c_list = NULL;
	token_list = NULL;
	while (*input)
	{
		if (manage_state_transition(&token_list, &input, &state,
				&c_list) == FAILUER)
			return (NULL);
	}
	if (state == STATE_SQUOTE || state == STATE_DQUOTE)
	{
		if (c_list)
			c_lstclear(&c_list, free);
		t_lstclear(&token_list, free);
		ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
		return (NULL);
	}
	return (token_list);
}

// int	lexer(char *input, t_token **token_list)
//{
//	t_token	*last_node;
//	t_token	*eof_node;

//	if (tokenizer(input, token_list) == FAILUER)
//		return (FAILUER);
//	if (!*token_list)
//		return (FAILUER);
//	last_node = t_lstlast(*token_list);
//	eof_node = t_lstnew(NULL);
//	if (!eof_node)
//		return (FAILUER);
//	eof_node->type = TOKEN_EOF;
//	last_node->next = eof_node;
//	return (SUCCESS);
//}

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
