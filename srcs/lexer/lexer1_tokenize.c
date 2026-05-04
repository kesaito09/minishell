/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer1_tokenize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:22:47 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/05 01:50:26 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static void	*fatal_exit_wrapper(t_token **lst, t_shared_info *info)
{
	t_lstclear(lst, free);
	fatal_exit(info);
	return (NULL);
}

int	word_len(char *input, char *charsplit, char *charignore,
		t_shared_info *info)
{
	int	len;
	int	tmp;

	(void)info;
	len = 0;
	while (input && input[len])
	{
		if ((ft_strchr(charsplit, input[len])) || (charignore
				&& input[len] == '&' && input[len + 1] == '&'))
			return (len);
		if (ft_strchr(charignore, input[len]))
		{
			tmp = strchr_len(input + len + 1, input[len]) + 1;
			if (!tmp)
			{
				ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
				return (FAILURE);
			}
			len += tmp + 1;
		}
		else
			len++;
	}
	return (len);
}

t_token	*tokenizer(char *input, t_shared_info *info)
{
	t_token			*lst;
	t_token			*new;
	t_token_type	type;
	int				n;

	lst = NULL;
	while (*input)
	{
		type = (t_token_type)str_type(input);
		if (type == TOKEN_WORD)
			n = word_len(input, SPLIT, QUOTE, info);
		else if (type == TOKEN_SPACE && input++)
			continue ;
		else
			n = operator_len(input);
		if (n == FAILURE)
			return (t_lstclear(&lst, free), NULL);
		new = t_lstnew(ft_strndup(input, n), free);
		if (!new)
			return (fatal_exit_wrapper(&lst, info));
		input += n;
		new->type = type;
		t_lstadd_back(&lst, new);
	}
	return (lst);
}
