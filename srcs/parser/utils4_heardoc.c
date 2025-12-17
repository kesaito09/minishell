/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_heardoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 21:02:26 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/16 21:34:48 by natakaha         ###   ########.fr       */
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

static bool	write_next_line(char *eof, int fd)
{
	char	*line;

	line = readline(">");
	if (!line)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("warning: ", 2);
		ft_putstr_fd("hear-document deliminated ", 2);
		ft_putendl_fd("by end-of-file(wanted 'EOF')", 2);
		return (false);
	}
	if (!ft_strcmp(eof, line))
		return (false);
	ft_putendl_fd(line, fd);
	return (true);
}

char	*heardoc(char *eof)
{
	char	*file;
	int		fd;

	file = heardoc_check();
	if (!file)
		return (NULL);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (NULL);
	while (write_next_line(eof, fd))
		;
	close(fd);
	return (file);
}
