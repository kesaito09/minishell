/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 06:33:13 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/20 04:48:30 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	return ;
}

static int	find_path(char ***path, char **envp)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = "tmp";
	while (envp[i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
		{
			tmp = ft_strdup(envp[i]);
			if (!tmp)
				return (FAILUER);
			break;
		}
		i++;
	}
	if (!tmp)
		return (FAILUER);
	*path = ft_split(tmp, ':');
	free(tmp);
	if (!path)
		return (FAILUER);
	return (SUCCESS);
}

static int	complete_path(char ***path, char **envp)
{
	int		i;
	char	*tmp;

	if (find_path(path, envp) == FAILUER)
		return (FAILUER);
	i = 0;
	while ((*path)[i])
	{
		tmp = (*path)[i];
		(*path)[i] = ft_strjoin((*path)[i], "/");
		if (!(*path)[i])
			return (FAILUER);
		free(tmp);
		i++;
	}
	return (SUCCESS);
}

char	**dup_split(char **envp)
{
	char	**new_env;
	int		i;

	new_env = (char **)ft_calloc(count_arr_elem(envp) + 1, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	return (new_env);
}

t_pipe	correct_info(char **envp)
{
	t_pipe	info;


	ft_bzero(&info, sizeof(t_pipe));
	if (complete_path(&(info.path), envp) == FAILUER)
		exit(1);
	info.envp = argv_token(envp);
	info.plist = NULL;
	info.pipe = false;
	info.fd[0] = -1;
	info.fd[1] = -1;
	info.fd_stdout = dup(1);
	info.fd_stdin = dup(0);
	return (info);
}
