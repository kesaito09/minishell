/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2_path_name_expantion.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 03:49:39 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/07 23:20:21 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

void	skip_star(char **input)
{
	while (**input && **input == '*')
		(*input)++;
}

int	increment(char **input, char **match)
{
	if (**input == '*' || **input != **match)
		return (SUCCESS);
	if (!**input || !**match)
		return (FAILUER);
	(*input)++;
	(*match)++;
	return(SUCCESS);
}

int	reset(char **input, char **d_name, char *start, char **match)
{
	if (**input == '*' || **input == **d_name)
		return (SUCCESS);
	*input = start;
	if (!**match)
		return (FAILUER);
	*d_name = (*match)++;
	return (SUCCESS);
}

int	star_skip(char **start, char **match, char **input, char *d_name)
{
	if (**input != '*')
		return (0);
	skip_star(input);
	if (!**input)
		return (1);
	*start = *input;
	*match = d_name;
	return (0);
}

bool	match_char(char *input, char *d_name)
{
	char	*start;
	char	*match;

	start = input;
	match = d_name;
	if (!input)
		return (false);
	while (*d_name)
	{
		if (star_skip(&start, &match, &input, d_name))
			break ;
		if (reset(&input, &d_name, start, &match) == FAILUER)
			return (false);
		increment(&input, &match);
	}
	skip_star(&input);
	if (!*input)
		return (true);
	return (false);
}

bool	check_hidden_file(char *input)
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
		token = t_lstnew(dent->d_name);
		if (!token)
			return (NULL);
		t_lstadd_back(&token_list, token);
	}
	closedir(dp);
	return (token_list);
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

 int main(void)
{
	t_token	*token_list = token_dir("M*");
	t_token	*token_list2 = token_dir(".*");

	print_token2(token_list);
	printf("\n");
	print_token2(token_list2);
}
