/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_redirect_error.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 02:13:45 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/24 08:41:27 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (false);
	if (S_ISDIR(statbuf.st_mode))
		return (true);
	return (false);
}

int	redirect_in_check(char *path)
{
	if (access(path, F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (FAILUER);
	}
	if (access(path, R_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Permission denied", 2);
		return (FAILUER);
	}
	if (is_directory(path))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Is a directory", 2);
		return (FAILUER);
	}
	return (SUCCESS);
}

int	redirect_out_check(char *path)
{
	if (access(path, F_OK) == -1)
		return (SUCCESS);
	if (access(path, W_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Permission denied", 2);
		return (FAILUER);
	}
	if (is_directory(path))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Is a directory", 2);
		return (FAILUER);
	}
	return (SUCCESS);
}

void	command_error_check(char *cmd, t_token *path_node)
{
	if ((path_node && ft_strncmp(cmd, "./", 2) && ft_strncmp(cmd, "../", 3)
			&& cmd[0] != '/') || access(cmd, F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	if (is_directory(cmd))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Is a directory", 2);
		exit(126);
	}
	else if (access(cmd, X_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Permission denied", 2);
		exit(126);
	}
}
