/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_special.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:43:42 by natakaha          #+#    #+#             */
/*   Updated: 2026/04/30 03:22:04 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_cmd.h"
#include "../../includes/main.h"

static char	*build_shlvl(char *shnum);

int	detect_ecode(int flag, t_shared_info *info)
{
	int	exit_code;

	exit_code = wait_pidlist(&info->plist);
	if (exit_code)
		return (exit_code);
	if (flag == FAILURE)
		return (1);
	return (0);
}

int	env_exit_code(int i, int flag, t_shared_info *info)
{
	char	*num;
	char	*env;
	t_token	*node;

	if (i == 0 && flag == FAILURE)
		i = 1;
	num = ft_itoa(i);
	if (!num)
		fatal_exit(info);
	env = ft_strjoin("?=", num);
	free(num);
	if (!env)
		fatal_exit(info);
	node = f_lstnew(env, 1);
	if (!node)
		return (free(env), fatal_exit(info), FAILURE);
	if (silent_export(node, info, TOP, 1) == FAILURE)
		return (t_lstclear(&node, free), fatal_exit(info), FAILURE);
	return (t_lstclear(&node, free), SUCCESS);
}

int	env_shlvl(t_shared_info *info)
{
	char	*shnum;
	char	*shlvl;
	t_token	*node;

	shnum = return_value("SHLVL", info->envp);
	if (!shnum)
		fatal_exit(info);
	shlvl = build_shlvl(shnum);
	free(shnum);
	if (!shlvl)
		fatal_exit(info);
	node = t_lstnew(shlvl, free);
	if (!node || silent_export(node, info, TOP, 0) == FAILURE)
		return (t_lstclear(&node, free), fatal_exit(info), FAILURE);
	return (t_lstclear(&node, free), SUCCESS);
}

static char	*build_shlvl(char *shnum)
{
	char	*num;
	char	*result;

	if (!*shnum || !ft_isnumber(shnum))
		return (ft_strdup("SHLVL=1"));
	num = ft_itoa(ft_atoi(shnum) + 1);
	if (!num)
		return (NULL);
	result = ft_strjoin("SHLVL=", num);
	free(num);
	return (result);
}

int	env_underscore(t_token *node, t_shared_info *info)
{
	char	*str;
	t_token	*tmp;

	if (!node)
		return (SUCCESS);
	node = t_lstlast(node);
	str = ft_strjoin("_=", node->token);
	if (!str)
		fatal_exit(info);
	tmp = t_lstnew(str, free);
	if (!tmp)
		return (free(str), fatal_exit(info), FAILURE);
	if (silent_export(tmp, info, TOP, 0) == FAILURE)
		return (t_lstclear(&tmp, free), fatal_exit(info), FAILURE);
	return (t_lstclear(&tmp, free), SUCCESS);
}
