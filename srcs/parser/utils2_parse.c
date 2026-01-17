/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:13:11 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/17 19:43:20 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/execution.h"

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
	tmp->next = NULL;
	deep_token_clear(tmp);
}

