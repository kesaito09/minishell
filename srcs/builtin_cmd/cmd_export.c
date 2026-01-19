/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 06:21:49 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/19 10:05:37 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_cmd.h"
#include "../../includes/execution.h"

static int	export_module(t_token *cmd, t_shared_info *info);

int	export(t_token *cmd, t_shared_info *info)
{
	while (cmd)
	{
		if (export_module(cmd, info) == FAILUER)
			return (FAILUER);
		cmd = cmd->next;
	}
	return (SUCCESS);
}

static int	export_module(t_token *cmd, t_shared_info *info)
{
	t_token	*env;

	if (is_valid_arg(cmd->token) == FAILUER)
		return (FAILUER);
	env = info->envp;
	while (env)
	{
		if (!ft_argcmp(cmd->token, env->token))
		{
			free(env->token);
			env->token = cmd->token;
			return (SUCCESS);
		}
		env = env->next;
	}
	env = t_lstnew(ft_strdup(cmd->token), free);
	if (!env)
		return (FAILUER);
	t_lstadd_back(&(info->envp), env);
	return (SUCCESS);
}

//int main(int ac, char **av)
//{
//	char	*str;

//	str = "b2b";
//	ft_putnbr_fd(find_arg(str, av), 1);
//	(void)ac;
//}
