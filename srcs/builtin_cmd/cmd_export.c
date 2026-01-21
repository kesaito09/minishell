/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 06:21:49 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/21 19:30:02 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_cmd.h"
#include "../../includes/execution.h"

static int	export_module(t_token *cmd, t_shared_info *info, int loc, int type);

int	export(t_token *cmd, t_shared_info *info)
{
	int	flag;

	while (cmd)
	{
		flag = export_module(cmd, info, BOTTOM, COMMAND);
		if (!flag)
			return (invalid_message(cmd->token), false);
		if (flag == FAILUER)
			return (FAILUER);
		cmd = cmd->next;
	}
	return (SUCCESS);
}

int	silent_export(t_token*cmd, t_shared_info *info, int loc)
{
	while (cmd)
	{
		if (export_module(cmd, info, loc, 0) <= 0)
			return (FAILUER);
		cmd = cmd->next;
	}
	t_lstclear(&cmd, free);
	return (SUCCESS);
}

static int	export_module(t_token *cmd, t_shared_info *info, int loc, int type)
{
	t_token	*env;

	if (!is_valid_arg(cmd->token))
		return (false);
	env = info->envp;
	while (env)
	{
		if (!ft_argcmp(cmd->token, env->token))
		{
			free(env->token);
			env->token = cmd->token;
			if (type != COMMAND)
				free(cmd);
			return (SUCCESS);
		}
		env = env->next;
	}
	env = t_lstnew(ft_strdup(cmd->token), free);
	if (!cmd)
		return (FAILUER);
	if (loc == BOTTOM)
		return (t_lstadd_back(&info->envp, env), SUCCESS);
	return (t_lstadd_front(&info->envp, env), SUCCESS);
}

//int main(int ac, char **av)
//{
//	char	*str;

//	str = "b2b";
//	ft_putnbr_fd(find_arg(str, av), 1);
//	(void)ac;
//}
