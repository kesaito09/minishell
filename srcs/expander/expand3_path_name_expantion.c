/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3_path_name_expantion.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 03:49:39 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/15 20:26:22 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expander.h"
#include "../../includes/minishell.h"
#include "../../includes/parser.h"

static bool	check_hidden_file(t_token *sub)
{
	if (!sub || !sub->token)
		return (false);
	return (sub->token[0] == '.');
}

t_token	*wild_card(t_token *sub)
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
		token = t_lstnew(dent->d_name);
		if (!token)
			return (NULL);
		t_lstadd_sort(&token_list, token);
	}
	return (closedir(dp), token_list);
}

int	insert_token(t_token *src, t_token *input)
{
	t_token	*tmp;
	int		n;

	if (!src || !input)
		return (FAILUER);
	if (!ft_strchr(src->token, '*') || input->type != SUB_TOKEN_GENERAL)
		return (1);
	tmp = wild_card(input);
	if (!tmp)
		return (FAILUER);
	n = t_lstsize(tmp);
	src->token = tmp->token;
	src->next = tmp->next;
	free(tmp);
	return (n);
}

int	path_name_expantion(t_token **token_list, t_list_type type)
{
	t_token	*tmp;
	int		n;

	tmp = *token_list;
	while (tmp)
	{
		n = insert_token(tmp, tmp->sub_token);
		if (n == FAILUER)
			return (FAILUER);
		if (type == FILE_LIST && n > 1)
		{
			ft_putendl_fd("ambiguous redirect", 2);
			return (FAILUER);
		}
		tmp = t_lstmove(tmp, n);
	}
	return (SUCCESS);
}
