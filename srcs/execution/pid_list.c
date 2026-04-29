/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 03:43:18 by naoki             #+#    #+#             */
/*   Updated: 2026/04/29 21:58:08 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static void			p_lstclear(t_pidlist *plist);
static t_pidlist	*pid_new(pid_t pid);
int					pid_fix(int status);

int	wait_pidlist(t_pidlist **plist)
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
	p_lstclear(tmp);
	*plist = NULL;
	return (pid_fix(status));
}

int	pid_fix(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		ft_putchar_fd('\n', 2);
		return (128 + WTERMSIG(status));
	}
	return (127);
}

int	pid_add_back(t_pidlist **plist, pid_t pid)
{
	t_pidlist	*tmp;

	if (!*plist)
	{
		*plist = pid_new(pid);
		if (!*plist)
			return (FAILURE);
		return (SUCCESS);
	}
	tmp = *plist;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = pid_new(pid);
	if (!tmp->next)
	{
		p_lstclear(*plist);
		*plist = NULL;
		return (FAILURE);
	}
	return (SUCCESS);
}

static t_pidlist	*pid_new(pid_t pid)
{
	t_pidlist	*plist;

	plist = (t_pidlist *)ft_calloc(sizeof(t_pidlist), 1);
	if (!plist)
		return (NULL);
	plist->pid = pid;
	return (plist);
}

static void	p_lstclear(t_pidlist *plist)
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
