/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 08:08:01 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/17 16:59:31 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.h"
#include "../../includes/execution.h"

void	builtin_exit(t_tree *branch, t_shared_info *info)
{
	free_tree_rec(branch);
	t_lstclear(&info->envp, free);
	exit(0);
}
