/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 00:00:00 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/01 05:20:54 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_prompt(t_token *envp)
{
	char	*line;
	char	*prompt;

	prompt = return_value("PS1", envp);
	if (!prompt || !*prompt)
	{
		free(prompt);
		prompt = ft_strdup("minishell$ ");
	}
	if (!prompt)
		return (NULL);
	line = readline(prompt);
	free(prompt);
	if (!line)
		return (NULL);
	if (!*line)
		return (free(line), ft_strdup(""));
	add_history(line);
	return (line);
}

char	*get_line(int fd)
{
	int		count;
	char	*trash;
	char	*line;
	char	*new;

	count = 100;
	line = ft_strdup("");
	new = ft_calloc(sizeof(char), 101);
	if (!line || !new)
		return (free(line), free(new), NULL);
	while (count > 0)
	{
		count = read(fd, new, 100);
		if (count < 0)
			break ;
		trash = line;
		line = ft_strjoin(line, new);
		free(trash);
		ft_bzero(new, 101);
		if (!line)
			return (free(new), NULL);
	}
	free(new);
	return (line);
}

t_token	*script_split(char *input, t_shared_info *info)
{
	int		len;
	t_token	*lst;

	lst = NULL;
	while (true)
	{
		len = word_len(input, "\n", NULL, info);
		if (t_lstnew_add_back(&lst, input, len, 0) == FAILURE)
			return (t_lstclear(&lst, free), NULL);
		input += len;
		if (!*input)
			return (lst);
		input++;
	}
}
