/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand4_ifs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 05:54:33 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/23 08:56:59 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expander.h"

static int	ifs_switcher(char c, char *ifs, t_ifs_state state);

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
		tmp = f_lstnew(ifs_join(&sub), node->type);
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

int	ifs_split(char *input, char *ifs, t_token **lst, t_ifs_state state)
{
	int	len;
	int	flag;

	len = 0;
	while (true)
	{
		flag = ifs_switcher(input[len], ifs, state);
		if (flag >> STATE_CHANGE & 1)
			state = is_ifs(input[len], ifs);
		if (flag >> INCREMENT & 1)
			input++;
		if (flag >> LEN_INCREMENT & 1)
			len++;
		if (flag >> ADD_LST & 1)
			if (t_lstnew_add_back(lst, input, len,
					SUB_TOKEN_IFS) == FAILUER)
				return (t_lstclear(lst, free), FAILUER);
		if (flag >> FINISH & 1)
			return (t_lstsize(*lst));
		if (flag >> ADD_LST & 1)
		{
			input += len + 1;
			len = 0;
		}
	}
}

static int	ifs_switcher(char c, char *ifs, t_ifs_state state)
{
	if (is_ifs(c, ifs) == SPCE)
	{
		if (state == WORD)
			return (1 << STATE_CHANGE | 1 << ADD_LST);
		return (1 << INCREMENT);
	}
	if (is_ifs(c, ifs) == IFS)
	{
		if (state != SPCE)
			return (1 << STATE_CHANGE | 1 << ADD_LST);
		return (1 << INCREMENT | 1 << STATE_CHANGE);
	}
	if (is_ifs(c, ifs) == WORD)
		return (1 << LEN_INCREMENT | 1 << STATE_CHANGE);
	if (is_ifs(c, ifs) == NLL && state != SPCE)
		return (1 << STATE_CHANGE | 1 << FINISH | 1 << ADD_LST);
	return (1 << FINISH);
}
