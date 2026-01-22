/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:49:23 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/22 22:20:28 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_cmd.h"
#include "../../includes/execution.h"

static int	echo_opn(t_token *node);
static int	echo_(t_token *node);
static bool	option_n(char *_n);


int	echo(t_token *node)
{
	if (!node->token)
		return (FAILUER);
	if (option_n(node->token))
		return (echo_opn(node->next));
	else
		return (echo_(node));
}

static bool	option_n(char *_n)
{
	int	i;


	if (_n[0] != '-')
		return (false);
	i = 1;
	while (_n[i])
	{
		if (_n[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static int	echo_opn(t_token *node)
{
	while (option_n(node->token))
		node = node->next;
	while (node)
	{
		ft_putstr_fd(node->token, 1);
		node = node->next;
		if (!node)
			return (SUCCESS);
		ft_putchar_fd(' ', 1);
	}
	return (SUCCESS);
}

static int	echo_(t_token *node)
{
	while (node)
	{
		ft_putstr_fd(node->token, 1);
		node = node->next;
		if (!node)
			break ;
		ft_putchar_fd(' ', 1);
	}
	ft_putchar_fd('\n', 1);
	return (SUCCESS);
}

//int main(int argc, char **argv)
//{
//	echo(argv);
//	(void)argc;
//}
