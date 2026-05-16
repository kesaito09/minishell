/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_heredoc_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 15:57:54 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/16 15:58:26 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	heredoc_change_token(t_shared_info *info, t_token *file_list,
		t_tree *branch)
{
	char	*delm;
	t_token	*node;

	node = file_list;
	while (node)
	{
		if (node->type == TOKEN_HEREDOC)
		{
			delm = node->token;
			node->token = NULL;
			node->token = heredoc(delm, branch, info);
			if (!node->token)
				return (FAILURE);
		}
		node = node->next;
	}
	return (SUCCESS);
}

int	search_heredoc(t_shared_info *info, t_tree *branch)
{
	if (!branch)
		return (SUCCESS);
	if (branch->file_list && heredoc_change_token(info, branch->file_list,
			branch) == FAILURE)
		return (FAILURE);
	if (search_heredoc(info, branch->left) == FAILURE)
		return (FAILURE);
	if (search_heredoc(info, branch->right) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
