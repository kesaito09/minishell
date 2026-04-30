/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 21:02:26 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/01 00:37:20 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"
#include <stdlib.h>

static char	*determine_heardoc_name(void);
static int	heardoc_write_one_line(char *delimiter, int fd,
				t_shared_info *info);
static int	heardoc_fork(char *delimiter, int fd, t_shared_info *info);

int			heardoc_write_context(char *delimiter, int fd, t_shared_info *info);

char	*heardoc(char *delimiter, t_tree *branch, t_shared_info *info)
{
	int		fd;
	char	*file;
	t_state	state;
	t_token	*new;

	file = determine_heardoc_name();
	if (!file)
		return (NULL);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (free(file), NULL);
	state = STATE_GENERAL;
	if (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '"'))
		state = STATE_DQUOTE;
	delimiter = expand_join(delimiter, info->envp, TOKEN_HEARDOC, info);
	if (heardoc_fork(delimiter, fd, info) == FAILURE)
		return (NULL);
	new = f_lstnew(ft_strdup(file), what_type(state));
	if (!new)
		return (free(file), NULL);
	t_lstadd_back(&(branch->heredoc), new);
	return (file);
}

static char	*determine_heardoc_name(void)
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

int	heardoc_write_context(char *delimiter, int fd, t_shared_info *info)
{
	int	flag;

	while (true)
	{
		flag = heardoc_write_one_line(delimiter, fd, info);
		if (flag == FAILURE)
			return (close(fd), free(delimiter), EXIT_FAILURE);
		else if (flag == END)
			return (close(fd), free(delimiter), EXIT_SUCCESS);
		else
			continue ;
	}
}

static int	heardoc_fork(char *delimiter, int fd, t_shared_info *info)
{
	int	pid;
	int	status;

	if (info->input)
		return (heardoc_no_fork(delimiter, fd, info));
	pid = fork();
	if (pid < 0)
		return (perror("heardoc"), FAILURE);
	status = 0;
	if (pid > 0)
	{
		setup_signal_exec();
		waitpid(pid, &status, 0);
		if (status == 0)
			return (SUCCESS);
		return (pid_fix(status));
	}
	if (pid == 0)
	{
		setup_signal_child();
		exit(heardoc_write_context(delimiter, fd, info));
	}
	return (SUCCESS);
}

static int	heardoc_write_one_line(char *delimiter, int fd, t_shared_info *info)
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
		return (heardoc_error_message(), FAILURE);
	if (!ft_strcmp(delimiter, line))
		return (free(line), END);
	if (!line)
		return (FAILURE);
	ft_putendl_fd(line, fd);
	return (free(line), SUCCESS);
}
