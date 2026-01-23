/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 08:08:01 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/23 09:36:05 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_cmd.h"
#include "../../includes/execution.h"

void	builtin_exit(t_shared_info *info)
{
	free_tree_rec(&info->branch);
	wait_pidlist(&info->plist);
	t_lstclear(&info->envp, free);
	rl_clear_history();
	exit(g_exit_code);
}
