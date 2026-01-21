/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 03:25:14 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/21 07:37:32 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expander.h"

static t_token	*quote_split(char **input);
static t_token	*expand_dollar(t_token *input);
static t_token	*replace_env(t_token *node, t_token *envp);

t_token	*get_sub_token(char *input, t_token *envp, t_token_type flag)
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
		if (new->type != SUB_TOKEN_SQUOTE && flag != TOKEN_HEREDOC)
		{
			new = expand_dollar(new);
			new = replace_env(new, envp);
		}
		t_lstadd_back(&lst, new);
	}
	return (lst);
}

static t_token	*quote_split(char **input)
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
	node = f_lstnew(ft_strndup(*input, n), what_type(state));
	*input += n;
	if (!node)
		return (NULL);
	return (node);
}

static t_token	*expand_dollar(t_token *input)
{
	t_token			*node;
	t_token			*new;
	char			*str;
	int				len;

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
		new = f_lstnew(ft_strndup(str, len), input->type);
		if (!new)
			return (t_lstclear(&node, free), NULL);
		str += len;
		t_lstadd_back(&node, new);
	}
}

static t_token	*replace_env(t_token *node, t_token *envp)
{
	t_token	*cur;
	t_token	*tmp;

	cur = node;
	tmp = NULL;
	while (cur)
	{
		if (cur->token[0] == '$' && cur->token[1])
		{
			cur->token = return_value(cur->token + 1, envp);
			if (cur->type == SUB_TOKEN_GENERAL)
				tmp = ifs_insert(cur, envp);
			if (!tmp)
				return (node);
			tmp = node;
		}
		cur = cur->next;
	}
	return (node);
}

//int	main(int ac, char **av, char **envp)
//{
//	t_token			*node;
//	t_shared_info	info;

//	if (ac == 1)
//		return (1);
//	info = collect_info(envp);
//	node = get_sub_token(av[1], info.envp);
//	print_token(node);
//}
