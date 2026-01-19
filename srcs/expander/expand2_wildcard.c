/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2_wildcard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 03:49:39 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/19 07:38:01 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expander.h"
#include "../../includes/parser.h"

static t_token	*return_valid_card(t_token *sub);
static bool		check_hidden_file(t_token *sub);
static bool		has_star(t_token *sub);

int	wildcard_expand(t_token *src, t_token **dest, t_list_type type)
{
	t_token	*tmp;
	int		n;

	if (!has_star(src) || type == ENV_LIST)
		return (false);
	tmp = return_valid_card(src);
	if (!tmp)
		return (false);
	n = t_lstsize(tmp);
	if (type == FILE_LIST && n > 1)
		return (ft_putendl_fd("ambiguous redirect", 2), free(tmp), FAILUER);
	*dest = tmp;
	return (n);
}

static t_token	*return_valid_card(t_token *sub)
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
			|| !search_file(sub, dent->d_name))
			continue ;
		token = t_lstnew(ft_strdup(dent->d_name), free);
		if (!token)
			return (NULL);
		t_lstadd_sort(&token_list, token);
	}
	return (closedir(dp), token_list);
}

static bool	has_star(t_token *sub)
{
	while (sub)
	{
		if (ft_strchr(sub->token, '*') && sub->type == SUB_TOKEN_GENERAL)
			return (true);
		sub = sub->next;
	}
	return (false);
}

static bool	check_hidden_file(t_token *sub)
{
	if (!sub || !sub->token)
		return (false);
	return (sub->token[0] == '.');
}
