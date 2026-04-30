/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
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

void		unset_module(t_shared_info *info, char *key);
static bool	is_valid_unset_arg(char *arg);
static void	unset_invalid_msg(char *arg);

int	unset(t_token *cmd, t_shared_info *info)
{
	int	flag;

	flag = SUCCESS;
	while (cmd)
	{
		if (!is_valid_unset_arg(cmd->token))
		{
			unset_invalid_msg(cmd->token);
			flag = FAILURE;
		}
		else
			unset_module(info, cmd->token);
		cmd = cmd->next;
	}
	return (flag);
}

static bool	is_valid_unset_arg(char *arg)
{
	int	i;

	if (!arg || !*arg)
		return (false);
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (false);
	i = 1;
	while (arg[i])
	{
		if (is_env_delimiter(arg[i]))
			return (false);
		i++;
	}
	return (true);
}

static void	unset_invalid_msg(char *arg)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}

int	silent_unset(t_token *node, t_shared_info *info)
{
	char	*key;
	int		len;

	while (node)
	{
		len = strchr_len(node->token, '=');
		if (len <= 1)
			continue ;
		key = ft_strndup(node->token, len);
		if (!key)
			fatal_exit(info);
		unset_module(info, key);
		free(key);
		node = node->next;
	}
	return (SUCCESS);
}

void	unset_module(t_shared_info *info, char *key)
{
	t_token	*node;
	t_token	*prev;

	node = info->envp;
	prev = NULL;
	while (node)
	{
		if (!ft_keycmp(key, node->token))
		{
			if (prev)
				prev->next = node->next;
			else
				info->envp = node->next;
			free(node->token);
			free(node);
			return ;
		}
		prev = node;
		node = node->next;
	}
}
