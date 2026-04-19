/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5_heardoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 21:02:26 by natakaha          #+#    #+#             */
/*   Updated: 2026/04/19 16:22:10 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static char	*determine_heardoc_name(void);
static int	heardoc_write_one_line(char *delimiter, int fd, t_shared_info *info);
static void	error_message(void);
static int	heardoc_write_context(char *delimiter, int fd, t_shared_info *info);

char	*heardoc(char *delimiter, t_shared_info *info)
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
	delimiter = expand_join(delimiter, info->envp, TOKEN_HEREDOC);	
	heardoc_write_context(delimiter, fd, info);
	new = f_lstnew(file, what_type(state));
	if (!new)
		return (free(file), NULL);
	t_lstadd_back(&(info->heardoc), new);
	return (free(delimiter), file);
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

static int	heardoc_write_context(char *delimiter, int fd, t_shared_info *info)
{
	int	flag;
	
	while (true)
	{
		flag = heardoc_write_one_line(delimiter, fd, info);
		if (flag == FAILUER)
			return (close(fd), free(delimiter), flag);
		else if (flag == END)
			return (close(fd), free(delimiter), flag);
		else
			continue ;
	}
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
		return (error_message(), END);
	if (!ft_strcmp(delimiter, line))
		return (free(line), END);
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
	ft_putendl_fd("by end-of-file(wanted 'delimiter')", 2);
}

void	heardoc_clear(t_token **heardoc)
{
	t_token	*tmp;
	
	tmp = *heardoc;
	while (tmp)
	{
		unlink(tmp->token);
		tmp = tmp->next;
	}
	t_lstclear(heardoc, free);
}
