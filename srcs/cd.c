/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 01:23:57 by natakaha          #+#    #+#             */
/*   Updated: 2025/11/29 01:52:55 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

void	cd(char **cmd)
{
	if (!ft_strcmp(cmd[0], "cd"))
		chdir(cmd[1]);
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