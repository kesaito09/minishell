/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3_wildcard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 03:49:39 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/17 17:15:29 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expander.h"
#include "../../includes/parser.h"

static bool	check_hidden_file(t_token *sub);

t_token	*is_valid_file(t_token *sub)
{
	DIR			*dp;
	t_token		*token_list;
	t_token		*token;
	t_dirent	*dent;

	token_list = NULL;
	dp = opendir(".");
	if (!dp)
		return (NULL);
	while (true)
	{
		dent = readdir(dp);
		if (!dent)
			break ;
		if (!ft_strncmp(dent->d_name, "..", 2) || (!check_hidden_file(sub)
				&& !ft_strncmp(dent->d_name, ".", 1))
			|| !match_char(sub, dent->d_name))
			continue ;
		token = t_lstnew(ft_strdup(dent->d_name), free);
		if (!token)
			return (NULL);
		t_lstadd_sort(&token_list, token);
	}
	return (closedir(dp), token_list);
}

int	insert_wild_card(t_token *src, t_token *input)
{
	t_token	*tmp;
	int		n;

	if (!src || !input)
		return (FAILUER);
	if (!ft_strchr(src->token, '*') || input->type != SUB_TOKEN_GENERAL)
		return (1);
	tmp = is_valid_file(input);
	if (!tmp)
		return (FAILUER);
	n = t_lstsize(tmp);
	src->token = tmp->token;
	src->next = tmp->next;
	free(tmp);
	return (n);
}

int	wildcard_expand(t_token **token_list, t_list_type type)
{
	t_token	*tmp;
	int		n;

	tmp = *token_list;
	while (tmp)
	{
		n = insert_wild_card(tmp, tmp->sub_token);
		if (n == FAILUER)
			return (FAILUER);
		if (type == ARG_LIST && n > 1)
		{
			ft_putendl_fd("ambiguous redirect", 2);
			return (FAILUER);
		}
		tmp = t_lstmove(tmp, n);
	}
	return (SUCCESS);
}

static bool	check_hidden_file(t_token *sub)
{
	if (!sub || !sub->token)
		return (false);
	return (sub->token[0] == '.');
}
