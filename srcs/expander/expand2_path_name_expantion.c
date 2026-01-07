/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2_path_name_expantion.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 03:49:39 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/02 13:48:08 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

void skip_star(char **input)
{
	while (**input && **input == '*')
		(*input)++;
}

int	match_char(char *input, char *d_name)
{
	char	*start;
	char	*match;

	start = NULL;
	while (*d_name)
	{
		if (*input == '*')
		{
			skip_star(&input);
			if (!*input)
				break;
			start = input;
			match = d_name;
		}
		if (*input != *d_name)
		{
			if (!start)
				return (FAILUER);
			input = start;
			d_name = (match++);
		}
        else
        {
            input++;
            d_name++;
        }
	}
	skip_star(&input);
	if (!*input)
		return (SUCCESS);
	return (FAILUER);
}

int check_hidden_file(char *input)
{
	if (!input)
		return (FAILUER);
	if (input[0] == '.')
		return (SUCCESS);
	return (FAILUER);
}

t_token	*token_dir(char *input)
{
	DIR		*dp;
	t_token	*token_list;
	t_token	*token;
	t_dirent *dent;

	token_list = NULL;
	if ((dp = opendir(".")) == NULL)
		return (NULL);
	while (1)
	{
		dent = readdir(dp);
		if (!dent)
			break ;
		if (!ft_strncmp(dent->d_name, "..", 2) || (check_hidden_file(input) == FAILUER && !ft_strncmp(dent ->d_name, ".", 1)))
			continue ;
		if (match_char(input, dent ->d_name) == FAILUER)
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

//void	print_token2(t_token *node)
//{
//	while (node)
//	{
//		ft_putendl_fd(node->token, 2);
//		node = node->next;
//	}
//}

//int main(void)
//{
//	t_token *token_list = token_dir("*");
//	t_token	*token_list2 = token_dir(".*");

//	print_token2(token_list);
//	printf("\n");
//	print_token2(token_list2);
//}


