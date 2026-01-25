/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 08:08:01 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/25 08:42:12 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_cmd.h"
#include "../../includes/execution.h"

static void	invalid_ecode(char *input);

void	builtin_exit(t_token *node, t_shared_info *info)
{
	int	num;

	if (!node)
		num = g_exit_code;
	else if (!ft_isnumber(node->token) || node->next)
	{
		invalid_ecode(node->token);
		num = 2;
	}
	else
		num = ft_atoi(node->token) % 256;
	free_tree_rec(&info->branch);
	wait_pidlist(&info->plist);
	t_lstclear(&info->envp, free);
	rl_clear_history();
	exit(num);
}

static void	invalid_ecode(char *input)
{
	ft_putstr_fd("minishell: exit: ", 2);
	if (!ft_isnumber(input))
	{
		ft_putstr_fd(input, 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	else
		ft_putendl_fd("too many arguments", 2);
	return ;
}
