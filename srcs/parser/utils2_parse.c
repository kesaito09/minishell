/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:13:11 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/25 09:24:38 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

int	count_element(char **s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
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

void	free_and_skip_one(t_token **cur)
{
	t_token	*tmp;

	if (!cur || !*cur)
		return ;
	tmp = *cur;
	*cur = (*cur)->next;
	t_lstdelone(tmp, free);
}

void	splice_to_list(t_token **list, t_token **cur)
{
	t_token	*head;

	head = *cur;
	*cur = head->next;
	head->next = NULL;
	t_lstadd_back(list, head);
}
