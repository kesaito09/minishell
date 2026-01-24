/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:42:39 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/24 15:12:20 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

t_tree	*tree_new(t_tree_type btype)
{
	t_tree	*node;

	node = (t_tree *)ft_calloc(sizeof(t_tree), 1);
	if (!node)
		return (NULL);
	node->b_type = btype;
	return (node);
}

void	free_tree_rec(t_tree **branch)
{
	if (!(*branch))
		return ;
	free_tree_rec(&(*branch)->left);
	free_tree_rec(&(*branch)->right);
	t_lstclear(&((*branch)->arg_list), free);
	t_lstclear(&((*branch)->file_list), free);
	t_lstclear(&((*branch)->env_list), free);
	free(*branch);
	*branch = NULL;
}
