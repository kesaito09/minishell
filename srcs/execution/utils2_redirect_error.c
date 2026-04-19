/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_redirect_error.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 02:13:45 by natakaha          #+#    #+#             */
/*   Updated: 2026/04/19 17:32:20 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

bool	is_directory(const char *path)
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

t_command_error	command_error_check(char *cmd)
{
	if (access(cmd, F_OK) == -1)
		return (COMMAND_NOT_FOUND);
	if (is_directory(cmd))
		return (IS_A_DIRECTORY);
	else if (access(cmd, X_OK) == -1)
		return (PERMISSION_DENIED);
	return (SUCCESS);
}

int	command_error_message(char *cmd, t_command_error errno)
{
	if (errno == COMMAND_NOT_FOUND)
	{
		ft_putstr_fd("minishell:", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": command not found", 2);
		return (127);
	}
	else if (errno == IS_A_DIRECTORY)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Is a directory", 2);
		return (126);
	}
	else if (errno == PERMISSION_DENIED)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Permission denied", 2);
		return (126);
	}
	return (SUCCESS);
}
