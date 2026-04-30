/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 19:38:09 by kesaitou          #+#    #+#             */
/*   Updated: 2026/04/29 21:58:08 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expander.h"
#include "../../includes/main.h"

static int	expand_token(t_token *node, t_list_type type, t_shared_info *info);
static bool	has_star(t_token *sub);

int	expander(t_token *node, t_shared_info *info, t_list_type l_type)
{
	int	n;

	while (node)
	{
		n = expand_token(node, l_type, info);
		if (n < 0)
			return (FAILURE);
		node = t_lstmove(node, n);
	}
	return (SUCCESS);
}

static int	expand_token(t_token *node, t_list_type type, t_shared_info *info)
{
	t_token	*tmp;
	t_token	*sub;
	int		n;

	sub = env_expand(node->token, info->envp, TOKEN_WORD);
	if (!has_star(sub) || type == ENV_LIST)
	{
		free(node->token);
		node->token = token_join(sub);
		return (t_lstclear(&sub, free), SUCCESS);
	}
	tmp = return_valid_card(sub, info);
	t_lstclear(&sub, free);
	n = t_lstsize(tmp);
	if (n == 0)
		return (1);
	if (type == FILE_LIST && n > 1)
		return (ft_putendl_fd("ambiguous redirect", 2), t_lstclear(&tmp, free),
			0);
	t_lstinsert(node, tmp);
	return (n);
}

static bool	has_star(t_token *sub)
{
	while (sub)
	{
		if (ft_strchr(sub->token, '*') && sub->type == SUB_TOKEN_GENERAL)
			return (true);
		sub = sub->next;
	}
	return (false);
}
