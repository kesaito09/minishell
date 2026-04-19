/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2_wildcard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 03:49:39 by kesaitou          #+#    #+#             */
/*   Updated: 2026/04/18 22:17:46 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expander.h"
#include "../../includes/parser.h"

static bool		check_hidden_file(t_token *sub);
static bool		file_name_validate(char *d_name, t_token *sub);

t_token	*return_valid_card(t_token *sub)
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
		if (!file_name_validate(dent->d_name, sub))
			continue ;
		token = t_lstnew(ft_strdup(dent->d_name), free);
		if (!token)
			return (closedir(dp), t_lstclear(&token_list, free), NULL);
		t_lstadd_sort(&token_list, token);
	}
	return (closedir(dp), token_list);
}

static bool	file_name_validate(char *d_name, t_token *sub)
{
	if (!ft_strcmp(d_name, ".") || !ft_strcmp(d_name, ".."))
		return (false);
	if (!check_hidden_file(sub) && d_name[0] == '.')
		return (false);
	if (!search_file(sub, d_name))
		return (false);
	return (true);
}

static bool	check_hidden_file(t_token *sub)
{
	if (!sub || !sub->token || sub->token[0] != '.')
		return (false);
	return (true);
}
