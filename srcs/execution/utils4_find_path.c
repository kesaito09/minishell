/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_find_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 06:33:13 by natakaha          #+#    #+#             */
/*   Updated: 2026/04/19 18:06:50 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static char	**strjoin_path_list(char **path_list);

t_token	*complete_path(t_token *envp)
{
	char	**path_lst;
	char	*path;

	path = return_value("PATH", envp);
	if (!path)
		return (NULL);
	else if (!*path)
		path_lst = path_split("./", ':');
	else if (path)
	{
		path_lst = path_split(path, ':');
		path_lst = strjoin_path_list(path_lst);
	}
	if (!path_lst)
		return (NULL);
	return (argv_token(path_lst));
}

static char	**strjoin_path_list(char **path_list)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path_list[i])
	{
		tmp = path_list[i];
		if (tmp[ft_strlen(tmp) - 1] == '/')
			continue ;
		path_list[i] = ft_strjoin(tmp, "/");
		if (!path_list[i])
			return (free_split(path_list), NULL);
		free(tmp);
		i++;
	}
	return (path_list);
}

char	*find_path(char **envp)
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
