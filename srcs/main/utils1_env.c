/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:43:42 by natakaha          #+#    #+#             */
/*   Updated: 2026/04/19 16:28:24 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_cmd.h"
#include "../../includes/main.h"

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

int	env_exit_code(int i, int flag, t_shared_info *info)
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

int	env_shlvl(t_shared_info *info)
{
	char	*shnum;
	int		n;
	char	*num;
	char	*shlvl;
	t_token	*node;

	shnum = return_value("SHLVL", info->envp);
	if (!shnum || !*shnum || !ft_isnumber(shnum))
		shlvl = ft_strjoin("SHLVL=", "1");
	else
		{
		n = ft_atoi(shnum);
		num = ft_itoa(n + 1);
		if (!num)
			return (FAILUER);
		shlvl = ft_strjoin("SHLVL=", num);
		free(num);
	}
	node = t_lstnew(shlvl, free);
	if (!node || silent_export(node, info, TOP, 0) == FAILUER)
		return (free(shnum), t_lstclear(&node, free), FAILUER);
	return (free(shnum), t_lstclear(&node, free), SUCCESS);
}

int	env_underscore(t_token *node, t_shared_info *info)
{
	char	*str;
	t_token	*tmp;

	if (!node)
		return (FAILUER);
	node = t_lstlast(node);
	str = ft_strjoin("_=", node->token);
	if (!str)
		return (FAILUER);
	tmp = t_lstnew(str, free);
	if (!tmp)
		return (FAILUER);
	if (silent_export(tmp, info, TOP, 0) == FAILUER)
		return (t_lstclear(&tmp, free), FAILUER);
	return (t_lstclear(&tmp, free), SUCCESS);
}
