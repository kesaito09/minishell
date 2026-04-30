/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_err_messages.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 04:00:00 by natakaha          #+#    #+#             */
/*   Updated: 2026/04/30 04:00:00 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/main.h"

int	err_no_such_file(t_shared_info *info, char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putendl_fd(": No such file or directory", 2);
	info->last_ecode = 1;
	return (FAILURE);
}

int	err_is_a_directory(t_shared_info *info, char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putendl_fd(": Is a directory", 2);
	info->last_ecode = 126;
	return (FAILURE);
}

int	err_permission_denied(t_shared_info *info, char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putendl_fd(": Permission denied", 2);
	info->last_ecode = 126;
	return (FAILURE);
}

int	err_command_not_found(t_shared_info *info, char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": command not found", 2);
	info->last_ecode = 127;
	return (FAILURE);
}

int	err_syntax(t_shared_info *info, char *tok)
{
	ft_putstr_fd("minishell: syntax error", 2);
	if (!tok)
		ft_putendl_fd(": unexpected newline", 2);
	else
	{
		ft_putstr_fd(" near unexpected token `", 2);
		ft_putstr_fd(tok, 2);
		ft_putendl_fd("'", 2);
	}
	info->last_ecode = 2;
	return (FAILURE);
}
