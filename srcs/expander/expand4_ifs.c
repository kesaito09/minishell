/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand4_ifs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 05:54:33 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/21 06:26:45 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expander.h"

static bool	has_type(t_token *sub, t_token_type type);

int	ifs_expand(t_token *sub, t_token *node, t_list_type type)
{
	t_token	*tmp;
	t_token	*lst;
	int		n;

	if (!has_type(sub, SUB_TOKEN_IFS))
		return (false);
	lst = NULL;
	while (sub)
	{
		tmp = f_lstnew(ifs_join(&sub), SUB_TOKEN_IFS);
		if (!tmp)
			return (t_lstclear(&lst, free), FAILUER);
		t_lstadd_back(&lst, tmp);
	}
	n = t_lstsize(lst);
	if (type == FILE_LIST && n > 1)
		return (ft_putendl_fd("ambiguous redirect", 2), free(lst), FAILUER);
	t_lstinsert(node, lst);
	return (n);
}

static bool	has_type(t_token *sub, t_token_type type)
{
	while (sub)
	{
		if (sub->type == type)
			return (true);
		sub = sub->next;
	}
	return (false);
}
