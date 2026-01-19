/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5_heardoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 21:02:26 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/19 07:47:50 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static char	*heardoc_name(void);
static int	write_heardoc(char *eof, int fd, t_token *envp, t_state state);
static void	error_message(void);

char	*heardoc(char *eof, t_token *envp)
{
	char	*file;
	int		fd;
	int		flag;
	t_state	state;

	file = heardoc_name();
	if (!file)
		return (NULL);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (NULL);
	state = STATE_GENERAL;
	if (ft_strchr(eof, '\'') || ft_strchr(eof, '"'))
		state = STATE_DQUOTE;
	eof = expand_join(eof, envp, TOKEN_HEREDOC);
	while (true)
	{
		flag = write_heardoc(eof, fd, envp, state);
		if (flag == FAILUER)
			return (close(fd), free(file), NULL);
		if (flag == END)
			break ;
	}
	close(fd);
	return (file);
}

static char	*heardoc_name(void)
{
	char	*file;
	char	*def;
	int		i;
	char	*num;

	def = ft_strdup(".heardoc_");
	if (!def)
		return (NULL);
	i = 1;
	while (true)
	{
		num = ft_itoa(i);
		if (!num)
			return (free(def), NULL);
		file = ft_strjoin(def, num);
		free(num);
		if (!file)
			return (free(def), NULL);
		if (access(file, F_OK) == -1)
			break ;
		i++;
	}
	return (free(def), file);
}

static int	write_heardoc(char *eof, int fd, t_token *envp, t_state state)
{
	char	*line;
	char	*expand;

	line = readline(">");
	if (!line)
		return (error_message(), END);
	if (!ft_strcmp(eof, line))
		return (END);
	if (state == STATE_GENERAL)
	{
		expand = expand_join(line, envp, TOKEN_WORD);
		free(line);
	}
	else
		expand = line;
	if (!expand)
		return (FAILUER);
	ft_putendl_fd(expand, fd);
	free(expand);
	return (SUCCESS);
}

static void	error_message(void)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("warning: ", 2);
	ft_putstr_fd("hear-document deliminated ", 2);
	ft_putendl_fd("by end-of-file(wanted 'EOF')", 2);
}
