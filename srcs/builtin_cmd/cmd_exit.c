/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 08:08:01 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/14 08:52:01 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.h"
#include "../../includes/execution.h"

void	builtin_exit(t_tree *branch, t_pipe *info)
{
	free_tree_rec(branch);
	t_lstclear(&info->envp, free);
	exit(0);
}
