/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 06:21:49 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/14 08:01:55 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.h"
#include "../../includes/execution.h"

int	export_module(t_token *cmd, t_pipe *info)
{
	t_token	*env;
	char	*arg;

	if (is_valid_arg(cmd->token) == FAILUER)
		return (FAILUER);
	arg = ft_strdup(cmd->token);
	if (!arg)
		return (FAILUER);
	env = info->envp;
	while (env)
	{
		if (!ft_argcmp(arg, env->token))
		{
			free(env->token);
			env->token = arg;
			return (SUCCESS);
		}
		env = env->next;
	}
	env = t_lstnew(arg);
	if (!env)
		return (free(arg), FAILUER);
	t_lstadd_back(&(info->envp), env);
	return (SUCCESS);
}

int	export(t_token *cmd, t_pipe *info)
{
	while (cmd)
	{
		export_module(cmd, info);
		cmd = cmd->next;
	}
	return (SUCCESS);
}

void	unset_module(t_pipe *info, char *key)
{
	t_token	*node;
	t_token	*tmp;

	node = info->envp;
	tmp = NULL;
	while (node)
	{
		if (!ft_keycmp(key, node->token))
		{
			if (tmp)
				tmp->next = node->next;
			else
				info->envp = node->next;
			free(node->token);
			free(node);
			return ;
		}
		tmp = node;
		node = node->next;
	}
}

int	unset(t_token *cmd, t_pipe *info)
{
	t_token	*key;

	key = cmd->next;
	while (key)
	{
		if (ft_strchr(key->token, '='))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(key->token, 2);
			ft_putendl_fd(": invalid parameter name", 2);
			return (FAILUER);
		}
		unset_module(info, key->token);
		key = key->next;
	}
	return (SUCCESS);
}

//int main(int ac, char **av)
//{
//	char	*str;

//	str = "b2b";
//	ft_putnbr_fd(find_arg(str, av), 1);
//	(void)ac;
//}
