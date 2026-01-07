/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 19:38:09 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/07 20:29:32 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expander.h"

#include <stdio.h>

void	print_sub_token(t_token *sub)
{
	while (sub)
	{
		fprintf(stderr, "--SUB: %s   TYPE: %d--\n", sub ->token, sub ->type);
		sub = sub ->next;
	}
}

void	print_token(t_token *token)
{
	while (token)
	{
		if (token ->sub_token)
		{
			print_sub_token(token ->sub_token);
		}
		token = token ->next;
	}	
}

int	expander(t_token **token_list, t_token *envp)
{
	if (expand_token(token_list, envp) == FAILUER)
		return (FAILUER);
	print_token(*token_list);
	return (SUCCESS);
}
