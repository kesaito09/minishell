/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:49:23 by natakaha          #+#    #+#             */
/*   Updated: 2025/11/29 01:32:56 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../commands.h"

static void	echo_opn(char **cmd)
{
	int		i;

	i = 2;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		i++;
		if (!cmd[i])
			return ;
		ft_putchar_fd(' ', 1);
	}
	return ;
}

static void	echo_(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		i++;
		if (!cmd[i])
			break ;
		ft_putchar_fd(' ', 1);
	}
	ft_putchar_fd('\n', 1);
	return ;
}

void	echo(char **cmd)
{
	int	i;

	i = 0;
	if (ft_strncmp(cmd[i], "echo\0", 5))
		return ;
	i++;
	if (!ft_strncmp(cmd[i], "-n", 3))
		echo_opn(cmd);
	else
		echo_(cmd);
}

//int main(int argc, char **argv)
//{
//	echo(argv);
//	(void)argc;
//}
