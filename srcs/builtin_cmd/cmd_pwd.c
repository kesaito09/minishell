/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 00:54:34 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/18 09:26:28 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_cmd.h"
#include "../../includes/execution.h"

/* this function must be in parent process*/

void	pwd(void)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	ft_putendl_fd(tmp, 1);
	free(tmp);
}

//int main(void)
//{
//	char	**str;
//	char	*tmp;
//	tmp = "pwd";
//	str = &tmp;
//	pwd(str);
//}