/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 21:02:26 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/15 18:07:39 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"
#include <stdlib.h>

static char	*determine_heardoc_name(void);
static int	heardoc_write_one_line(char *delimiter, int fd);
static int	heardoc_fork(char *delimiter, int fd,
				t_shared_info *info, t_token *cur);
int			heardoc_write_context(char *delimiter, int fd);

char	*heardoc(char *delimiter, t_tree *branch, t_shared_info *info,
	t_token *cur)
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
	cur->next->token = NULL;
	delimiter = expand_join(delimiter, info->envp, TOKEN_HEARDOC, info);
	if (heardoc_fork(delimiter, fd, info, cur) != EXIT_SUCCESS)
		return (free(delimiter), unlink(file), free(file), NULL);
	free(delimiter);
	new = f_lstnew(ft_strdup(file), what_type(state));
	if (!new)
		return (unlink(file), free(file), NULL);
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

int	heardoc_write_context(char *delimiter, int fd)
{
	int	flag;

	while (true)
	{
		flag = heardoc_write_one_line(delimiter, fd);
		if (flag == FAILURE)
			return (close(fd), free(delimiter), EXIT_FAILURE);
		else if (flag == END)
			return (close(fd), free(delimiter), EXIT_SUCCESS);
		else
			continue ;
	}
}

static int	heardoc_fork(char *delimiter, int fd, t_shared_info *info, t_token *cur)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid < 0)
		return (perror("heardoc"), EXIT_FAILURE);
	status = 0;
	if (pid > 0)
	{
		setup_signal_exec();
		waitpid(pid, &status, 0);
		if (status == 0)
			return (EXIT_SUCCESS);
		status = pid_fix(status);
		env_exit_code(status, FAILURE, info);
		return (status);
	}
	setup_signal_child();
	info->last_ecode = heardoc_write_context(delimiter, fd);
	t_lstclear(&cur, free);
	builtin_exit(NULL, info);
	return (EXIT_SUCCESS);
}

static int	heardoc_write_one_line(char *delimiter, int fd)
{
	char	*line;

	line = readline(">");
	if (!line)
		return (heardoc_error_message(), END);
	if (!ft_strcmp(delimiter, line))
		return (free(line), END);
	if (!line)
		return (FAILURE);
	ft_putendl_fd(line, fd);
	return (free(line), SUCCESS);
}
