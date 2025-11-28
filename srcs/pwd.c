/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 00:54:34 by natakaha          #+#    #+#             */
/*   Updated: 2025/11/29 01:43:22 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

/* this function must be in parent process*/

void	pwd(char **cmd)
{
	char	*tmp;
	if (!ft_strcmp(cmd[0], "pwd"))
	{
		tmp = getcwd(NULL, 0);
		ft_putendl_fd(tmp, 1);
		free(tmp);
	}
}

//int main(void)
//{
//	char	**str;
//	char	*tmp;
//	tmp = "pwd";
//	str = &tmp;
//	pwd(str);
//}