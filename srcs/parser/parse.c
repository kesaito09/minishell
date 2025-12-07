/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 04:00:08 by kesaitou          #+#    #+#             */
/*   Updated: 2025/12/06 06:57:37 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

char	*get_token(t_token **token_list)
{
	static t_token *s_token;
	t_token			*tmp;

	if (!token_list || !*token_list)
		return (NULL);
	s_token = *token_list;
	tmp = s_token;
	(s_token) = s_token;
	return (tmp);
}

int	check_token(t_token *token)
{
	
	
	
	
	
	
	
	
	
}

//シンタックスエラーの時点でリターン

void	parser(char *line)
{
	t_token	**token_list;
	t_token	*token;


	token_list = NULL;
	my_lex(line, token_list);
	while (1)
	{
		token = get_token(token_list);
		if (!token)
			return (NULL);
		if (check_token(token) == ERROR)
			return (ERROR);
		
	}
	
	
	
	
	

}
