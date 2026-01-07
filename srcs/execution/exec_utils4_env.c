/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils4_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:12:49 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/08 04:22:19 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h" 

int	local_env(t_token *env, t_pipe *info)
{
	t_token	*tmp;
	char	*copy;

	while (env)
	{
		copy = ft_strdup(env->token);
		if (!copy)
			return (FAILUER);
		tmp = t_lstnew(copy, 0);
		if (!tmp)
			return (FAILUER);
		tmp->type = 1;
		t_lstadd_front(&(info->envp), tmp);
		env = env->next;
	}
	return (FAILUER);
}
