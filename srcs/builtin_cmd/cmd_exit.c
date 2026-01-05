/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 08:08:01 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/05 08:14:53 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.h"
#include "../../includes/execution.h"

void	builtin_exit(t_tree *branch, t_pipe *info)
{
	free_tree_rec(branch);
	free_split(info->path);
	t_lstclear(&info->envp, free);
	exit(0);
}
