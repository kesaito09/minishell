/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 19:38:09 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/21 06:26:25 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expander.h"

static int	expand_token(t_token *node, t_token *envp, t_list_type type);

int	expander(t_token *node, t_shared_info *info, t_list_type l_type)
{
	int	n;

	while (node)
	{
		n = expand_token(node, info->envp, l_type);
		if (n < 0)
			return (FAILUER);
		node = t_lstmove(node, n);
	}
	return (SUCCESS);
}

static int	expand_token(t_token *node, t_token *envp, t_list_type type)
{
	t_token	*sub_token;
	int		flag;

	sub_token = get_sub_token(node->token, envp, TOKEN_WORD);
	if (!sub_token)
		return (FAILUER);
	flag = wildcard_expand(sub_token, node, type);
	if (flag != false)
		return (t_lstclear(&sub_token, free), flag);
	flag = ifs_expand(sub_token, node, type);
	if (flag != false)
		return (t_lstclear(&sub_token, free), flag);
	free(node->token);
	node->token = token_join(sub_token);
	t_lstclear(&sub_token, free);
	if (!node->token)
		return (FAILUER);
	return (1);
}
