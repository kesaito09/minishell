/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 03:25:14 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/17 17:13:43 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expander.h"

t_token	*quote_split(char **input)
{
	t_state	state;
	t_token	*node;
	int		n;

	state = STATE_GENERAL;
	n = 0;
	if (ft_strchr("'\"", **input))
		state = **input;
	if (state == STATE_GENERAL)
		n = word_len(*input, "'\"", NULL);
	else if (state == STATE_SQUOTE || state == STATE_DQUOTE)
		n = strchr_len(*input + 1, state) + 2;
	if (n <= 1)
		return (NULL);
	node = t_lstnew(ft_strndup(*input, n), free);
	*input += n;
	if (!node)
		return (NULL);
	node->type = what_type(state);
	return (node);
}

t_token	*expand_dollar(t_token *input)
{
	t_token	*node;
	t_token	*new;
	char	*str;
	int		len;

	str = input->token;
	node = NULL;
	while (true)
	{
		len = strchr_len(str, '$');
		if (len < 0 && node && !*str)
			return (free(input), node);
		else if (len < 0 && !*str)
			return (input);
		else if (len < 0)
			len = ft_strlen(str);
		if (len == 0)
			len = envlen(str + 1) + 1;
		new = t_lstnew(ft_strndup(str, len), free);
		if (!new)
			return (t_lstclear(&node, free), NULL);
		str += len;
		t_lstadd_back(&node, new);
	}
}

t_token	*get_sub_token(char *input)
{
	t_token	*lst;
	t_token	*new;
	char	*tmp;

	lst = NULL;
	while (*input)
	{
		new = quote_split(&input);
		if (!new)
			return (t_lstclear(&lst, free), NULL);
		if (new->type != SUB_TOKEN_GENERAL)
		{
			tmp = ft_substr(new->token, 1, ft_strlen(new->token) - 2);
			free(new->token);
			new->token = tmp;
		}
		if (new->type != SUB_TOKEN_SQUOTE)
			new = expand_dollar(new);
		t_lstadd_back(&lst, new);
	}
	return (lst);
}
