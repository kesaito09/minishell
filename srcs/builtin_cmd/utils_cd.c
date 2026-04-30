/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 04:00:00 by natakaha          #+#    #+#             */
/*   Updated: 2026/04/30 04:00:00 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_cmd.h"
#include "../../includes/execution.h"
#include "../../includes/main.h"

int	env_oldpwd(t_shared_info *info)
{
	t_token	*node;
	char	*pwd;
	char	*new_env;

	pwd = return_value("PWD", info->envp);
	if (!pwd)
		fatal_exit(info);
	new_env = ft_strjoin("OLDPWD=", pwd);
	free(pwd);
	if (!new_env)
		fatal_exit(info);
	node = t_lstnew(new_env, free);
	if (!node)
		return (free(new_env), fatal_exit(info), FAILURE);
	if (silent_export(node, info, BOTTOM, 0) == FAILURE)
		return (t_lstclear(&node, free), fatal_exit(info), FAILURE);
	return (t_lstclear(&node, free), SUCCESS);
}

int	env_pwd(t_shared_info *info)
{
	t_token	*node;
	char	*pwd;
	char	*new_env;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (FAILURE);
	new_env = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (!new_env)
		fatal_exit(info);
	node = t_lstnew(new_env, free);
	if (!node)
		return (free(new_env), fatal_exit(info), FAILURE);
	if (silent_export(node, info, BOTTOM, 0) == FAILURE)
		return (t_lstclear(&node, free), fatal_exit(info), FAILURE);
	return (t_lstclear(&node, free), SUCCESS);
}
