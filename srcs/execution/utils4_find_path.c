/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_find_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 06:33:13 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/18 09:55:44 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static char	*find_path(char **envp);

t_token	*complete_path(char **envp)
{
	char	*path_str;
	char	**path_lst;
	char	*tmp;
	int		i;

	if (!envp || !*envp)
		return (NULL);
	path_str = find_path(envp);
	if (!path_str)
		return (NULL);
	path_lst = ft_split(path_str, ':');
	if (!path_lst)
		return (NULL);
	i = 0;
	while (path_lst[i])
	{
		tmp = path_lst[i];
		path_lst[i] = ft_strjoin(tmp, "/");
		if (!path_lst[i])
			return (free_split(path_lst), NULL);
		free(tmp);
		i++;
	}
	return (argv_token(path_lst));
}

static char	*find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_argcmp("PATH", envp[i]))
			return (envp[i]);
		i++;
	}
	return (NULL);
}
