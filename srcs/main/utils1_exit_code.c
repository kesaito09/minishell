/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_exit_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:43:42 by natakaha          #+#    #+#             */
/*   Updated: 2026/04/18 07:22:51 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_cmd.h"
#include "../../includes/execution.h"
#include "../../includes/minishell.h"

int	detect_ecode(int flag, t_shared_info *info)
{
	int	exit_code;

	exit_code = wait_pidlist(&info->plist);
	if (exit_code)
		return (exit_code);
	if (flag == FAILUER)
		return (1);
	return (0);
}

int	export_exit_code(int i, int flag, t_shared_info *info)
{
	char	*num;
	char	*env;
	t_token	*node;

	if (i == 0 && flag == FAILUER)
		i = 1;
	num = ft_itoa(i);
	if (!num)
		return (FAILUER);
	env = ft_strjoin("?=", num);
	if (!env)
		return (FAILUER);
	node = f_lstnew(env, 1);
	if (!node)
		return (free(env), FAILUER);
	if (silent_export(node, info, TOP, 1) == FAILUER)
		return (t_lstclear(&node, free), FAILUER);
	return (t_lstclear(&node, free), SUCCESS);
}
