/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:22:47 by kesaitou          #+#    #+#             */
/*   Updated: 2025/11/28 14:06:05 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int lexer(char *input)
{
	t_token_list	*current;
	t_token_list	*new_elem;
	t_state			state;

	state = STATE_GENERAL;
	while (*input)
	{
		if (*input == '\'')
		{
			state = STATE_SQUOTE;

			
		}
		if (*input == '"')
		{
			state = STATE_DQUOTE;
			
		}
		
		
		
		
		
		
		
		
		
		
	}
	
	
	
		
	
	
	
}



int main(void)
{
	char *test1 = "ls -l | awk '{print $1}' > outfile";

	
	
	
	
	
}


