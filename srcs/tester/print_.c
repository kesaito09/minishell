/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 21:32:05 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/18 13:42:37 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	print_token(t_token *token)
{
	while (token)
	{
		fprintf(stderr, "--TOKEN: %s  TYPE: %d--\n", token->token, token->type);
		token = token ->next;
	}
}

void	print_tree(t_tree *branch)
{
	if (!branch)
		return ;
	print_token(branch->arg_list);
	print_token(branch->file_list);
	print_token(branch->env_list);
	ft_dprintf(2, "%d\n", branch->b_type);
	print_tree(branch->left);
	print_tree(branch->right);
}
