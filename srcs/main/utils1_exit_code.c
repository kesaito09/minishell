/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_exit_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 05:43:42 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/17 19:58:51 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/commands.h"
#include "../../includes/execution.h"

void	error_exit(char *str, int errno)
{
	perror(str);
	exit(errno);
}

int	detect_ecode(int flag, t_shared_info *info)
{
	int	exit_code;

	exit_code = wait_pidlist(&info->plist);
	if (exit_code)
		return (exit_code);
	if (!exit_code && flag == FAILUER)
		return (1);
	return (0);
}
