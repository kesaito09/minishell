/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 01:23:57 by natakaha          #+#    #+#             */
/*   Updated: 2025/11/29 16:00:40 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.h"
#include "../../includes/pipex.h"

void	cd(char **cmd)
{
	if (chdir(cmd[1]))
		error_exit(cmd, cmd[0], 1);
	free_path(cmd);
	exit(0);
}

//int main(void)
//{
//	char	*pwd1;
//	char	**cmd;

//	pwd1 = "pwd";
//	cmd = (char **)malloc(sizeof(char *) * 2);
//	cmd[0] = "cd";
//	cmd[1] = "../";
//	pwd(&pwd1);
//	cd(cmd);
//	pwd(&pwd1);
//	free(cmd);
//}