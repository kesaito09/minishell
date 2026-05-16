/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 04:00:00 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/16 15:55:45 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	heredoc_error_message(void)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("warning: ", 2);
	ft_putstr_fd("here-document deliminated ", 2);
	ft_putendl_fd("by end-of-file(wanted 'delimiter')", 2);
}

void	heredoc_unlink_files(t_token *heredoc)
{
	while (heredoc)
	{
		unlink(heredoc->token);
		heredoc = heredoc->next;
	}
}

void	heredoc_free_list(t_token **heredoc)
{
	t_lstclear(heredoc, free);
}

void	heredoc_clear(t_token **heredoc)
{
	heredoc_unlink_files(*heredoc);
	heredoc_free_list(heredoc);
}

void	heredoc_unlink_tree(t_tree *branch)
{
	if (!branch)
		return ;
	heredoc_unlink_tree(branch->left);
	heredoc_unlink_tree(branch->right);
	heredoc_unlink_files(branch->heredoc);
}
