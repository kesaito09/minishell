/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 04:00:00 by natakaha          #+#    #+#             */
/*   Updated: 2026/04/30 04:00:00 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	heardoc_error_message(void)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("warning: ", 2);
	ft_putstr_fd("hear-document deliminated ", 2);
	ft_putendl_fd("by end-of-file(wanted 'delimiter')", 2);
}

int	heardoc_no_fork(char *delimiter, int fd, t_shared_info *info)
{
	if (heardoc_write_context(delimiter, fd, info) == EXIT_SUCCESS)
		return (SUCCESS);
	return (FAILURE);
}

void	heardoc_clear(t_token **heardoc)
{
	t_token	*tmp;

	tmp = *heardoc;
	while (tmp)
	{
		unlink(tmp->token);
		tmp = tmp->next;
	}
	t_lstclear(heardoc, free);
}
