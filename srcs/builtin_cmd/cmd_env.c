/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 06:29:07 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/18 09:26:28 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_cmd.h"
#include "../../includes/execution.h"

void	env(t_token *node, t_shared_info *info)
{
	t_token	*tmp;

	tmp = info->envp;
	if (node->next && !ft_strcmp(node->next->token, "-a"))
	{
		while (tmp)
		{
			ft_putendl_fd(tmp->token, 1);
			tmp = tmp->next;
		}
	}
	if (!tmp)
		return ;
	while (tmp)
	{
		if (tmp->type == 0)
			ft_putendl_fd(tmp->token, 1);
		tmp = tmp->next;
	}
}
