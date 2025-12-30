/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_heardoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 21:02:26 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/30 12:33:21 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static char	*heardoc_check(void)
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

static int	write_next_line(char *eof, int fd, t_token *envp)
{
	char	*line;
	char	*expand;

	line = readline(">");
	if (!line)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("warning: ", 2);
		ft_putstr_fd("hear-document deliminated ", 2);
		ft_putendl_fd("by end-of-file(wanted 'EOF')", 2);
		return (END);
	}
	expand = expand_str(line, envp);
	free(line);
	if (!expand)
		return (FAILUER);
	if (!ft_strcmp(eof, expand))
		return (FAILUER);
	ft_putendl_fd(expand, fd);
	free(expand);
	return (SUCCESS);
}

char	*heardoc(char *eof, t_token *envp)
{
	char	*file;
	int		fd;
	int		flag;

	file = heardoc_check();
	if (!file)
		return (NULL);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (NULL);
	while (true)
	{
		flag = write_next_line(eof, fd, envp);
		if (flag == FAILUER)
			return (close(fd), free(file), NULL);
		if (flag == END)
			break ;
	}
	close(fd);
	return (file);
}
