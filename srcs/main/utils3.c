/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 09:53:27 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/18 09:54:57 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_shared_info	collect_info(char **envp)
{
	t_shared_info	info;


	ft_bzero(&info, sizeof(t_shared_info));
	info.envp = argv_token(envp);
	info.plist = NULL;
	info.pipe = false;
	info.fd[0] = -1;
	info.fd[1] = -1;
	info.fd_stdout = dup(1);
	info.fd_stdin = dup(0);
	return (info);
}

char	*handle_prompt(void)
{
	char	*line;

	line = readline("minishell$ ");
	if (!line)
		return (NULL);
	if (!*line)
	{
		free(line);
		handle_prompt();
	}
	add_history(line);
	return (line);
}

char	*get_line(int fd)
{
	char	*tmp;
	char	*trash;
	char	*line;

	tmp = "tmp";
	line = NULL;
	while (tmp)
	{
		trash = line;
		tmp = get_next_line(fd);
		line = ft_strjoin(line, tmp);
		free(tmp);
		free(trash);
		if (!line)
			return (NULL);
	}
	return (line);
}
