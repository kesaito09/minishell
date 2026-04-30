/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_path_search.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 06:33:13 by natakaha          #+#    #+#             */
/*   Updated: 2026/04/19 22:00:00 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/main.h"

static void	strjoin_path_list(char **path_list, t_shared_info *info);

t_token	*complete_path(t_token *envp, t_shared_info *info)
{
	char	**path_lst;
	char	*path;
	t_token	*result;

	path = return_value("PATH", envp);
	if (!path)
		child_fatal_exit(info);
	if (!*path)
		path_lst = path_split("./", ':', info);
	else
	{
		path_lst = path_split(path, ':', info);
		strjoin_path_list(path_lst, info);
	}
	free(path);
	result = argv_token(path_lst);
	free_split(path_lst);
	if (!result)
		child_fatal_exit(info);
	return (result);
}

static void	strjoin_path_list(char **path_list, t_shared_info *info)
{
	int		i;
	char	*tmp;

	i = 0;
	while (path_list[i])
	{
		tmp = path_list[i];
		if (tmp[ft_strlen(tmp) - 1] == '/')
		{
			i++;
			continue ;
		}
		path_list[i] = ft_strjoin(tmp, "/");
		if (!path_list[i])
		{
			path_list[i] = tmp;
			child_fatal_exit(info);
		}
		free(tmp);
		i++;
	}
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
