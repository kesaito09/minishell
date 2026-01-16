/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils4_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:12:49 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/16 10:28:22 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	local_env(t_token *env, t_pipe *info)
{
	t_token	*tmp;

	while (env)
	{
		if (!env->token)
			return (FAILUER);
		tmp = t_lstnew(ft_strdup(env->token), free);
		if (!tmp)
			return (FAILUER);
		tmp->type = 1;
		t_lstadd_front(&(info->envp), tmp);
		env = env->next;
	}
	return (FAILUER);
}
