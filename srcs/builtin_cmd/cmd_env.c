/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 06:29:07 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/20 05:22:33 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.h"
#include "../../includes/execution.h"

int	env(t_token *node, t_pipe *info)
{
	t_token	*tmp;

	tmp = info->envp;
	if (!tmp)
		return ;
	while (tmp)
	{
		ft_putendl_fd(tmp->token, 1);
		tmp = tmp->next;
	}
	(void)node;
}