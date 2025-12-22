/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils4_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:12:49 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/22 20:50:03 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

bool	has_cmd(t_token *args)
{
	t_token	*tmp;

	tmp = args;
	while (tmp)
	{
		if (tmp->type == COMMAND)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

int	local_env(t_token *env, t_pipe *info)
{
	t_token	*tmp;
	char	*copy;

	while (env)
	{
		copy = ft_strdup(env->token);
		if (!copy)
			return (FAILUER);
		tmp = t_lstnew(copy);
		if (!tmp)
			return (FAILUER);
		tmp->type = 1;
		t_lstadd_front(&(info->envp), tmp);
	}
	return (FAILUER);
}