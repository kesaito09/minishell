/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec5_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:55:18 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/18 09:26:28 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_cmd.h"
#include "../../includes/execution.h"

static int	set_local_env(t_token *env, t_shared_info *info);

int	manage_envp(t_tree *branch, t_shared_info *info, int fd_in, int fd_out)
{
	t_token	*env;

	env = branch->env_list;
	if (branch->arg_list)
		manage_cmd(branch, info, fd_in, fd_out);
	else
		if (set_local_env(env, info) == FAILUER)
			return (FAILUER);
	return (SUCCESS);
}

static int	set_local_env(t_token *env, t_shared_info *info)
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