/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 09:53:27 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/21 19:13:46 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	env_shlvl(t_shared_info *info);

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
	export_exit_code(0, SUCCESS, &info);
	if (env_shlvl(&info) == FAILUER
		|| export_exit_code(0, SUCCESS, &info) == FAILUER)
		ft_bzero(&info, sizeof(t_shared_info));
	return (info);
}

static int	env_shlvl(t_shared_info *info)
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
		if (n <= 0)
			shlvl = ft_strjoin("SHLVL=", "1");
		else
		{
			num = ft_itoa(n + 1);
			shlvl = ft_strjoin("SHLVL=", num);
			free(num);
		}
	}
	node = t_lstnew(shlvl, free);
	if (!node)
		return (free(shnum), FAILUER);
	return (free(shnum), silent_export(node, info, TOP));
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
