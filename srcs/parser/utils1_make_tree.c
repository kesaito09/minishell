/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_make_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:42:39 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/07 16:47:55 by natakaha         ###   ########.fr       */
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

void	tree_add_left(t_tree **branch, t_tree *node)
{
	(*branch)->left = node;
}

void	tree_add_right(t_tree **branch, t_tree *node)
{
	(*branch)->right = node;
}

void	free_split(char **cmd)
{
	int	i;

	if (!cmd || !*cmd)
		return ;
	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

void	free_tree_rec(t_tree *branch)
{
	if (!branch)
		return ;
	free_tree_rec(branch->left);
	free_tree_rec(branch->right);
	t_lstclear(&(branch->arg_list), free);
	t_lstclear(&(branch->file_list), free);
	t_lstclear(&(branch->env_list), free);
	free(branch);
}
