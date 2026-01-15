/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils4_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:12:49 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/15 19:29:36 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	local_env(t_token *env, t_pipe *info)
{
	t_token	*tmp;
	char	*copy;

	while (env)
	{
		copy = env->token;
		if (!copy)
			return (FAILUER);
		tmp = t_lstnew(copy);
		if (!tmp)
			return (FAILUER);
		tmp->type = 1;
		t_lstadd_front(&(info->envp), tmp);
		env = env->next;
	}
	return (FAILUER);
}
