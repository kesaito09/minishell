/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 01:23:57 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/18 09:26:28 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_cmd.h"
#include "../../includes/execution.h"

void	cd(t_token *node)
{
	char	*cd_;

	if (!node->next)
		return ;
	cd_ = node->next->token;
	if (chdir(cd_))
		return ;
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