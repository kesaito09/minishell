/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:49:23 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/20 05:15:25 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.h"
#include "../../includes/execution.h"

static int	echo_opn(t_token *node)
{
	t_token	*tmp;

	tmp = node->next->next;
	while (tmp)
	{
		ft_putstr_fd(tmp->token, 1);
		tmp = tmp->next;
		if (!tmp)
			return (SUCCESS);
		ft_putchar_fd(' ', 1);
	}
	return (SUCCESS);
}

static int	echo_(t_token *node)
{
	t_token	*tmp;

	tmp = node->next;
	while (tmp)
	{
		ft_putstr_fd(tmp->token, 1);
		tmp = tmp->next;
		if (!tmp)
			return (SUCCESS);
		ft_putchar_fd(' ', 1);
	}
	ft_putchar_fd('\n', 1);
	return (SUCCESS);
}

int	echo(t_token *node)
{
	t_token	*tmp;

	tmp = node->next;
	if (!tmp->token)
		return (FAILUER);
	if (!ft_strncmp(tmp->token, "-n", 3))
		return (echo_opn(node));
	else
		return (echo_(node));
}

//int main(int argc, char **argv)
//{
//	echo(argv);
//	(void)argc;
//}
