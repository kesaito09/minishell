/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3_path_name_expantion.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 03:49:39 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/12 11:59:53 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"
#include "../../includes/execution.h"
#include "../../includes/expander.h"

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
		if (!ft_strncmp(dent->d_name, "..", 2)
			|| !match_char(sub, dent->d_name)
			|| (!check_hidden_file(sub) && !ft_strncmp(dent->d_name, ".", 1)))
			continue ;
		token = t_lstnew(dent->d_name);
		if (!token)
			return (NULL);
		t_lstadd_back(&token_list, token);
	}
	closedir(dp);
	return (token_list);
}

int insert_token(t_token *src, t_token *src_next, t_token *new)
{
	char	*trash;
	int		n;

	if (!src || !new)
		return (0);
	trash = src ->token;
	src ->token = new ->token;
	src ->next = new ->next;
	n = t_lstsize(src);
	t_lstlast(src) ->next = src_next;
	free(trash);
	free(new);
	return (n);
}

int	manage_insert_token(t_token *src, t_token *(*f)(t_token *), t_token *input)
{
	t_token	*tmp;

	if (!src || !input)
		return (1);
	if (!ft_strchr(src->token, '*') || input ->type != SUB_TOKEN_GENERAL)
		return (1);
	tmp = f(input);
	if (!tmp)
		return (1);
	return (insert_token(src, src ->next, tmp));
}

int path_name_expantion(t_token **token_list, t_list_type type)
{
	t_token	*tmp;
	int		n;

	tmp = *token_list;
	while (tmp)
	{
		n = manage_insert_token(tmp, wild_card, tmp->sub_token);
		if (n == 0)
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

void	print_token2(t_token *node)
{
	while (node)
	{
		ft_putendl_fd(node->token, 2);
		node = node->next;
	}
}

//int	main(int argc, char **argv)
//{
//	t_token	*node;

//	if (argc < 2)
//		return (0);
//	node = tokenizer(argv[1]);
//	wildcard(node);
//	print_token2(node);
//}
