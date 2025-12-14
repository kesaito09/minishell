/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 06:33:13 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/10 02:06:36 by natakaha         ###   ########.fr       */
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
			return (free_path(*path), FAILUER);
		free(tmp);
		i++;
	}
	return (SUCCESS);
}

t_pipe	correct_info(char **envp)
{
	t_pipe	info;


	ft_bzero(&info, sizeof(t_pipe));
	if (complete_path(&(info.path), envp) == FAILUER)
		error_exit(NULL, "path not found", 2);
	info.envp = envp;
	info.plist = pid_new(getpid());
	info.pipe = false;
	info.fd[0] = -1;
	info.fd[1] = -1;
	info.fd_stdout = dup(1);
	info.fd_stdin = dup(0);
	return (info);
}
