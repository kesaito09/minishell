/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 06:21:49 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/26 11:54:16 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_cmd.h"
#include "../../includes/execution.h"

void	unset_module(t_shared_info *info, char *key);

int	unset(t_token *cmd, t_shared_info *info)
{
	t_token	*key;

	key = cmd;
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
			return (FAILUER);
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
