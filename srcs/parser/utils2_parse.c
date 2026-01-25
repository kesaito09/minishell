/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:13:11 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/25 09:24:38 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/execution.h"

int	count_element(char **s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	free_split(char **cmd)
{
	int	i;

	if (!cmd || !*cmd)
		return ;
	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

void	free_and_skip_one(t_token **cur)
{
	t_token	*tmp;

	if (!cur || !*cur)
		return ;
	tmp = *cur;
	*cur = (*cur)->next;
	t_lstdelone(tmp, free);
}

void	syntax_error_msg(char *err_token)
{
	ft_putstr_fd("minishell: syntax error", 2);
	if (!err_token)
		ft_putendl_fd(": unexpected newline", 2);
	else
	{
		ft_putstr_fd(" near unexpected token `", 2);
		ft_putstr_fd(err_token, 2);
		ft_putendl_fd("'", 2);
	}
	g_exit_code = 2;
}
