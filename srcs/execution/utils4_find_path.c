/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_find_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 06:33:13 by natakaha          #+#    #+#             */
/*   Updated: 2026/04/19 17:40:03 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

t_token	*complete_path(char *path)
{
	char	**path_lst;
	char	*tmp;
	int		i;

	
	path_lst = path_split(path, ':');
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
