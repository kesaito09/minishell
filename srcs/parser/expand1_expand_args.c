/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1_expand_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:51:16 by natakaha          #+#    #+#             */
/*   Updated: 2025/11/23 16:46:07 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

static void	manage_quote_expander(char **av, t_state *state)
{
	if (**av == '\'')
	{
		*state = STATE_SQUOTE;
		
	}
	else if (**av == '"')
	{
		*state = STATE_DQUOTE;
		(*av)++;
	}
}

int manage_state_general_expander(char **av, t_state *state)
{
	manage_quote_expander(av, state);



}

t_token *state_transition(char *av)
{
	t_state state;

	state = STATE_GENERAL;
	while (*av)
	{
		if (state == STATE_GENERAL)
		{
			if (manage_state_general_expander(&av, state) == FAILUER)
				return (FAILUER);
		}
		else if (state == STATE_SQUOTE)
		{
			if (manage_state_squote(input, state, c_list) == FAILUER)
				return (FAILUER);
		}
		else if (state == STATE_DQUOTE)
		{
			if (manage_state_dquote(input, state, c_list) == FAILUER)
				return (FAILUER);
		}
	}
	return (SUCCESS);
	
	
	
	
}

t_token	*expand_args(t_token *token_list)
{
	t_token *new_token_list;

	new_token_list = NULL;
	while (token_list)
	{
		new_token_list = state_transition(token_list ->token);
		
		
		
		
	}
	
	
	
	
	
	
}

int expander(t_token *token_list, char *ifs)
{
	
	
	
	
	
	
	
	
	
	
}

