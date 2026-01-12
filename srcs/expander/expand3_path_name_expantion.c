/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3_path_name_expantion.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 03:49:39 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/12 11:14:04 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"
#include "../../includes/execution.h"
#include "../../includes/expander.h"

static bool	check_hidden_file(t_token *sub)
{
	if (!sub || sub->token)
		return (false);
	if (sub->token[0] == '.')
		return (true);
	return (false);
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

int	insert_token(t_token *src, t_token *(*f)(t_token *), t_token *input)
{
	char	*trash;
	t_token	*tmp;
	int		n;

	trash = src->token;
	if (!ft_strchr(src->token, '*'))
		return (1);
	tmp = f(input);
	if (!tmp)
		return (1);
	n = t_lstsize(tmp);
	free(trash);
	src->token = tmp->token;
	src->next = tmp->next;
	free(tmp);
	return (n);
}

// int		pathname_expantion(t_token **token_list)
// {

// }

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
