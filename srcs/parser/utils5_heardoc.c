/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5_heardoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 21:02:26 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/23 11:27:48 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static char	*heardoc_name(void);
static int	write_heardoc(char *eof, int fd, t_shared_info *info, t_state stat);
static void	error_message(void);

char	*heardoc(char *eof, t_shared_info *info)
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
	eof = expand_join(eof, info->envp, TOKEN_HEREDOC);
	while (true)
	{
		flag = write_heardoc(eof, fd, info, state);
		if (flag == FAILUER)
			return (close(fd), free(file), free(eof), NULL);
		if (flag == END)
			break ;
	}
	close(fd);
	return (free(eof), file);
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

static int	write_heardoc(char *eof, int fd, t_shared_info *info, t_state state)
{
	char	*line;

	if (info->input)
	{
		line = ft_strdup(info->input->token);
		free_and_skip_one(&info->input);
	}
	else
		line = readline(">");
	if (!line)
		return (error_message(), END);
	if (!ft_strcmp(eof, line))
		return (free(line), END);
	if (state == STATE_GENERAL)
		line = expand_join(line, info->envp, TOKEN_WORD);
	if (!line)
		return (FAILUER);
	ft_putendl_fd(line, fd);
	return (free(line), SUCCESS);
}

static void	error_message(void)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("warning: ", 2);
	ft_putstr_fd("hear-document deliminated ", 2);
	ft_putendl_fd("by end-of-file(wanted 'EOF')", 2);
}
