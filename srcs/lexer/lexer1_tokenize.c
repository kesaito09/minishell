/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:22:47 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/16 16:01:49 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

// void	init_state(t_state_tab *state)
// {
// 	state->s_main = STATE_GENERAL;
// 	state->s_sub = STATE_GENERAL;
// }

int	logical_len(char *input)
{
	if (ft_strchr("|&<>", input[0]) && input[0] == input[1])
		return (2);
	return (1);
}

int	str_type(char *op)
{
	if (ft_strchr("&|<>", op[0]) && op[0] == op[1])
		return ((op[0] + 128));
	else if (ft_strchr("|<>()", op[0]))
		return (op[0]);
	else if (ft_strchr(" \t\n", op[0]))
		return (TOKEN_SPACE);
	else
		return (TOKEN_WORD);
}

int	word_len(char *input, char *charsplit, char *charignore)
{
	int	len;
	int	tmp;

	len = 0;
	if (!input)
		return (-1);
	while (input[len])
	{
		if ((ft_strchr(charsplit, input[len]))
			|| (charignore && input[len] == '&' && input[len + 1] == '&'))
			return (len);
		if (ft_strchr(charignore, input[len]))
		{
			tmp = strchr_len(input + len + 1, input[len]) + 1;
			if (!tmp)
			{
				ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
				return (-1);	
			}
			len += tmp + 1;
		}
		else
			len++;
	}
	return (len);
}

t_token	*tokenizer(char *input)
{
	t_token		*lst;
	t_token		*new;
	t_token_type	type;
	int		n;

	lst = NULL;
	while (*input)
	{
		type = (t_token_type)str_type(input);
		if (type == TOKEN_WORD)
			n = word_len(input, SPLIT, QUOTE);
		else if (type == TOKEN_SPACE && input++)
			continue ;	
		else
			n = logical_len(input);
		new = t_lstnew(ft_strndup(input, n), free);
		if (!new)
			return (t_lstclear(&lst, free), NULL);
		input += n;
		new->type = type;
		t_lstadd_back(&lst, new);
	}
	return (lst);
}

// t_token	*token_to_sub(t_token *token_list)
// {
// 	if (!token_list)
				
	
	
	
	
	
	
// }



// int main(int ac, char **av)
// {
// 	if (ac == 1)
// 		return (0);
// 	print_token(tokenizer(av[1]));
// }

// int	token_len(char *input, char *charset)
// {
// 	int	len;
// 	int	tmp;

// 	if (!input)
// 		return (-1);
// 	len = input_len(input, charset);
// 	tmp = strchr_len(input, '&');
// 	if (input[tmp + 1] == '&' && tmp < len && tmp >= 0)
// 		len = tmp;
// 	return (len);
// }



// int	state_check(char c, int state)
// {
// 	if (c == '\'' || c == '"' || c == '$')
// 	{
// 		if ((c == '\'' || c == '"') && state == c)
// 			return (STATE_GENERAL);
// 		else if (state == STATE_GENERAL)
// 			return (c);
// 		else if (state == STATE_DQUOTE && c == '$')
// 			return (STATE_DOLLER_DQUOTE);
// 		else
// 			return (state);
// 	}
// 	return (state);
// }
// //
// char	*hundle_state_general_word(char **input)
// {
// 	int		n;
// 	char	*str;
// 	t_token	*node;

// 	if (!*input)
// 		return (NULL);
// 	n = token_len(*input, "'\" \t\n|()<>");
// 	if (n == 0 && ft_strchr(" \t\n", *input))
// 	{
// 		*input++;
// 		return (NULL);
// 	}
// 	else if (n == 0 && ft_strchr("'\"", *input))
// 		return (NULL);
// 	else if (n == 0)
// 		n = logical_len(*input);
// 	str = ft_strndup(*input, n);
// 	input += n;
// 	return (str);
// }

// //クォートをDUPするやつポインtな勧めてる
// char	*manage_state_quote(char **input, t_state state)
// {
// 	int		n;
// 	char	*str;
// 	t_token	*node;

// 	*input++;
// 	n = strchr_len(*input, state);
// 	if (n == -1)
// 	{
// 		ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
// 		return (NULL);
// 	}
// 	str = ft_strndup(input + 1, n - 1);
// 	*input += n;
// 	return (str);
// }

// char	*make_str(char **input)
// {

// }

// // t_token	*manage_state_transition(char *input)
// // {
// // 	t_state	state;
// // 	t_state	*new;
// // 	t_state	*lst;
// // 	int		n;

// // 	lst = NULL;
// // 	new = NULL;
// // 	while (*input)
// // 	{
// // 		state = state_check(state, *input);
// // 		if (state == STATE_GENERAL)
// // 			new = manage_state_general(&input);
// // 		else if (state == STATE_DQUOTE || state == STATE_SQUOTE)
// // 			new = manage_state_quote(&input, state);
// // 		if (!new)
// // 			return (NULL);
// // 		t_lstadd_back(&lst, new);
// // 	}
// // 	return (lst);
// // }

// t_token	*tokenizer(char *input)
// {
// 	(void)input;
// 	return (NULL);
// }
