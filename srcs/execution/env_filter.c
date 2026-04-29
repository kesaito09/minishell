/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_filter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 00:00:00 by natakaha          #+#    #+#             */
/*   Updated: 2026/04/20 00:00:00 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

t_token	*discard_local_env(t_token *envp)
{
	t_token	*new_env;
	t_token	*tmp;

	new_env = NULL;
	while (envp)
	{
		if (envp->type != 0)
		{
			free_and_skip_one(&envp);
			continue ;
		}
		tmp = envp->next;
		envp->next = NULL;
		t_lstadd_back(&new_env, envp);
		envp = tmp;
	}
	return (new_env);
}
