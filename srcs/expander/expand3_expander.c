/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 19:38:09 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/18 15:22:21 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expander.h"

int	expander(t_token *node, t_shared_info *info, t_list_type l_type)
{
	t_token	*sub_token;
	t_token	*wild;
	char	*trash;

	while (node)
	{
		sub_token = get_sub_token(node->token, info->envp, TOKEN_WORD);
		if (!sub_token)
			return (FAILUER);
		wild = wildcard_expand(sub_token, l_type);
		if (!wild)
		{
			trash = node->token;
			node->token = expand_join(node->token, info->envp, TOKEN_WORD);
			free(trash);
			node = node->next;
		}
		else
			node = t_lstinsert(node, wild)->next;
	}
	return (SUCCESS);
}
