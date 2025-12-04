/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 06:33:13 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/01 22:41:06 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
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

t_pipe	correct_info(int argc, char **argv, char **envp)
{
	t_pipe	info;


	ft_bzero(&info, sizeof(t_pipe));
	if (complete_path(&(info.path), envp) == FAILUER)
		error_exit(NULL, "path not found", 2);
	info.argv = argv;
	info.envp = envp;
	info.argc = argc;
	info.plist = pid_new(getpid());
	info.fd_out[0] = -1;
	info.fd_out[1] = -1;
	info.fd_in[0] = -1;
	info.fd_in[1] = -1;
	info.fd_stdout = dup(1);
	info.fd_stdin = dup(0);	
	return (info);
}
