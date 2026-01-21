/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 00:54:34 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/21 17:01:00 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_cmd.h"
#include "../../includes/execution.h"

/* this function must be in parent process */

int	pwd(t_shared_info *info)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (!tmp)
		tmp = return_value("PWD", info->envp);
	if (!tmp || !*tmp)
		return (free(tmp),
			ft_putendl_fd("minishell: pwd: No such file or directory", 2),
			FAILUER);
	ft_putendl_fd(tmp, 1);
	free(tmp);
	return (SUCCESS);
}

//int main(void)
//{
//	char	**str;
//	char	*tmp;
//	tmp = "pwd";
//	str = &tmp;
//	pwd(str);
//}