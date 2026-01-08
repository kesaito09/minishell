/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3_path_name_expantion.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 03:49:39 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/08 10:14:39 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

static bool	check_hidden_file(char *input)
{
	if (!input)
		return (false);
	if (input[0] == '.')
		return (true);
	return (false);
}

t_token	*token_dir(char *input)
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
			|| !match_char(input, dent->d_name)
			|| (!check_hidden_file(input) && !ft_strncmp(dent->d_name, ".", 1)))
			continue ;
		token = t_lstnew(dent->d_name, 0);
		if (!token)
			return (NULL);
		t_lstadd_back(&token_list, token);
	}
	closedir(dp);
	return (token_list);
}

void	wildcard(t_token *node)
{
	char	*input;
	t_token	*tmp;

	input = node->token;
	tmp = token_dir(input);
	free(input);
	if (!tmp)
			return ;
	node->token = tmp->token;
	node->next = tmp->next;
	free(tmp);
}

// int		pathname_expantion(t_token **token_list)
// {

// }

// void	print_token2(t_token *node)
// {
// 	while (node)
// 	{
// 		ft_putendl_fd(node->token, 2);
// 		node = node->next;
// 	}
// }

// int main(void)
// {
// 	t_token *token_list = token_dir("*Ma*f**l");
// 	t_token	*token_list2 = token_dir(".*");

// 	print_token2(token_list);
// 	printf("\n");
// 	print_token2(token_list2);
// }

//  int main(void)
// {
// 	t_token	*token_list = token_dir("M*");
// 	t_token	*token_list2 = token_dir(".*");

// 	print_token2(token_list);
// 	printf("\n");
// 	print_token2(token_list2);
// }
