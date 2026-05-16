/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 21:02:26 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/16 15:55:59 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"
#include <stdlib.h>

static char	*determine_heredoc_name(void);
static int	heredoc_write_one_line(char *delimiter, int fd);
static int	heredoc_fork(char *delimiter, int fd, char *file,
				t_shared_info *info);
int			heredoc_write_context(char *delimiter, int fd);

char	*heredoc(char *delimiter, t_tree *branch, t_shared_info *info)
{
	int		fd;
	char	*file;
	t_state	state;
	t_token	*new;

	file = determine_heredoc_name();
	if (!file)
		return (NULL);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (free(file), NULL);
	state = STATE_GENERAL;
	if (ft_strchr(delimiter, '\'') || ft_strchr(delimiter, '"'))
		state = STATE_DQUOTE;
	delimiter = expand_join(delimiter, info->envp, TOKEN_HEREDOC, info);
	if (heredoc_fork(delimiter, fd, file, info) != EXIT_SUCCESS)
		return (free(delimiter), unlink(file), free(file), NULL);
	free(delimiter);
	new = f_lstnew(ft_strdup(file), what_type(state));
	if (!new)
		return (unlink(file), free(file), NULL);
	t_lstadd_back(&(branch->heredoc), new);
	return (file);
}

static char	*determine_heredoc_name(void)
{
	char	*file;
	char	*def;
	int		i;
	char	*num;

	def = ft_strdup(".heredoc_");
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
		free(file);
		i++;
	}
	return (free(def), file);
}

int	heredoc_write_context(char *delimiter, int fd)
{
	int	flag;

	while (true)
	{
		flag = heredoc_write_one_line(delimiter, fd);
		if (flag == FAILURE)
			return (close(fd), free(delimiter), EXIT_FAILURE);
		else if (flag == END)
			return (close(fd), free(delimiter), EXIT_SUCCESS);
		else
			continue ;
	}
}

static int	heredoc_fork(char *delimiter, int fd, char *file,
		t_shared_info *info)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid < 0)
		return (perror("heredoc"), EXIT_FAILURE);
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
	free_tree_rec(&info->branch);
	info->last_ecode = heredoc_write_context(delimiter, fd);
	free(file);
	builtin_exit(NULL, info);
	return (EXIT_SUCCESS);
}

static int	heredoc_write_one_line(char *delimiter, int fd)
{
	char	*line;

	line = readline(">");
	if (!line)
		return (heredoc_error_message(), END);
	if (!ft_strcmp(delimiter, line))
		return (free(line), END);
	if (!line)
		return (FAILURE);
	ft_putendl_fd(line, fd);
	return (free(line), SUCCESS);
}
