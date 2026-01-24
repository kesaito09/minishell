/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 09:53:27 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/24 15:42:41 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	env_shlvl(t_shared_info *info);

t_shared_info	collect_info(char **envp)
{
	t_shared_info	info;

	ft_bzero(&info, sizeof(t_shared_info));
	info.envp = argv_token(envp);
	info.fd[0] = -1;
	info.fd[1] = -1;
	info.fd_stdout = dup(1);
	info.fd_stdin = dup(0);
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
		num = ft_itoa(n + 1);
		if (!num)
			return (FAILUER);
		shlvl = ft_strjoin("SHLVL=", num);
		free(num);
	}
	node = t_lstnew(shlvl, free);
	if (!node || silent_export(node, info, TOP, 0) == FAILUER)
		return (free(shnum), t_lstclear(&node, free), FAILUER);
	return (free(shnum), t_lstclear(&node, free), SUCCESS);
}

char	*handle_prompt(t_token *envp)
{
	char	*line;
	char	*prompt;

	prompt = return_value("PS1", envp);
	if (!prompt || !*prompt)
	{
		free(prompt);
		prompt = ft_strdup("minishell$");
	}
	line = readline(prompt);
	free(prompt);
	if (!line)
		return (NULL);
	if (!*line)
	{
		free(line);
		return ("");
	}
	add_history(line);
	return (line);
}

char	*get_line(int fd)
{
	int		count;
	char	*trash;
	char	*line;
	char	*new;

	line = NULL;
	count = 100;
	line = ft_strdup("");
	new = ft_calloc(sizeof(char), 100);
	if (!line || !new)
		return (free(line), free(new), NULL);
	while (count > 0)
	{
		count = read(fd, new, 100);
		trash = line;
		line = ft_strjoin(line, new);
		free(trash);
		ft_bzero(new, 101 * sizeof(char));
		if (!line)
			return (free(new), NULL);
	}
	free(new);
	return (line);
}

t_token	*script_split(char *input)
{
	int		len;
	t_token	*lst;

	lst = NULL;
	while (true)
	{
		len = word_len(input, "\n", NULL);
		if (t_lstnew_add_back(&lst, input, len, 0) == FAILUER)
			return (t_lstclear(&lst, free), NULL);
		input += len;
		if (!*input)
			return (lst);
		input++;
	}
}
