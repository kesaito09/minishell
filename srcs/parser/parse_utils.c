/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 02:56:58 by kesaitou          #+#    #+#             */
/*   Updated: 2025/12/07 03:28:47 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

int	list_to_next(t_token **token_list, t_token_type type)
{
	if (!token_list || (*token_list)->type != type)
		return (ERROR);
	*token_list = (*token_list)->next;
	return (SUCCESS);
}

// int	main(void)
// {

    
    
    
    
    
// }