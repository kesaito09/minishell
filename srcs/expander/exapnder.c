/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exapnder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 20:24:47 by kesaitou          #+#    #+#             */
/*   Updated: 2025/12/22 20:33:17 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"





int expander(t_token **token_list, t_token	*envp)
{
	t_token *cur_list;

	cur_list = *token_list;
	while (cur_list)
	{
		if (expand_variables(&cur_list, envp) == FAILUER)
			return (FAILUER);
		if (expand_ifs(&cur_list) == FAILUER)
			return (FAILUER);
		
		
		
	}
	
	
	
	
	
	
	
}
