/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 09:53:27 by natakaha          #+#    #+#             */
/*   Updated: 2026/04/19 16:20:50 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_shlvl(t_shared_info *info);

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
		|| env_exit_code(0, SUCCESS, &info) == FAILUER)
		t_lstclear(&info.envp, free);
	return (info);
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
