/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1_pid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 03:43:18 by naoki             #+#    #+#             */
/*   Updated: 2026/01/05 08:42:26 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

t_pidlist	*pid_new(pid_t pid)
{
	t_pidlist	*plist;

	plist = (t_pidlist *)ft_calloc(sizeof(t_pidlist), 1);
	if (!plist)
		return (NULL);
	plist->pid = pid;
	return (plist);
}

void	pid_add_back(t_pidlist **plist, pid_t pid)
{
	t_pidlist	*tmp;

	if (!*plist)
	{
		*plist = pid_new(pid);
		return ;
	}
	tmp = *plist;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = pid_new(pid);
	if (!tmp->next)
	{
		free_pid(*plist);
		plist = NULL;
	}
}

void	free_pid(t_pidlist *plist)
{
	t_pidlist	*tmp;

	if (!plist)
		return ;
	tmp = plist;
	while (plist)
	{
		tmp = tmp->next;
		free(plist);
		plist = tmp;
	}
}

int	waitpid_plist(t_pidlist **plist)
{
	int			status;
	t_pidlist	*tmp;

	if (!*plist)
		return (0);
	status = 0;
	tmp = *plist;
	while (*plist)
	{
		waitpid((*plist)->pid, &status, 0);
		(*plist) = (*plist)->next;
	}
	free_pid(tmp);
	*plist = NULL;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		ft_putchar_fd('\n', 2);
		return (128 + WTERMSIG(status));
	}
	return (127);
}
