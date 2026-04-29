/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 06:21:49 by natakaha          #+#    #+#             */
/*   Updated: 2026/04/29 21:58:08 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_cmd.h"
#include "../../includes/execution.h"
#include "../../includes/main.h"

static int	export_module(t_token *cmd, t_shared_info *info, int loc, int type);

int	export(t_token *cmd, t_shared_info *info)
{
	int	flag;

	while (cmd)
	{
		flag = export_module(cmd, info, BOTTOM, 0);
		if (!flag)
			return (invalid_message(cmd->token), FAILURE);
		cmd = cmd->next;
	}
	return (SUCCESS);
}

int	silent_export(t_token *cmd, t_shared_info *info, int loc, int type)
{
	int	flag;

	flag = 0;
	while (cmd)
	{
		flag = export_module(cmd, info, loc, type);
		if (flag == false)
			return (flag);
		cmd = cmd->next;
	}
	return (SUCCESS);
}

static int	export_module(t_token *cmd, t_shared_info *info, int loc, int type)
{
	t_token	*env;
	char	*dup;

	if (!is_valid_arg(cmd->token))
		return (false);
	env = info->envp;
	while (env)
	{
		if (!ft_argcmp(cmd->token, env->token))
		{
			dup = ft_strdup(cmd->token);
			if (!dup)
				fatal_exit(info);
			free(env->token);
			env->token = dup;
			env->type = cmd->type;
			return (SUCCESS);
		}
		env = env->next;
	}
	dup = ft_strdup(cmd->token);
	if (!dup)
		fatal_exit(info);
	env = f_lstnew(dup, type);
	if (!env)
		return (free(dup), fatal_exit(info), FAILURE);
	if (loc == BOTTOM)
		return (t_lstadd_back(&info->envp, env), SUCCESS);
	return (t_lstadd_front(&info->envp, env), SUCCESS);
}
