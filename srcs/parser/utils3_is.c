/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_is.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 09:41:30 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/22 23:39:24 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

bool	is_builtin(char *token)
{
	if (!token)
		return (false);
	if (!ft_strcmp(token, "cd")
		|| !ft_strcmp(token, "env")
		|| !ft_strcmp(token, "export")
		|| !ft_strcmp(token, "unset")
		|| !ft_strcmp(token, "echo")
		|| !ft_strcmp(token, "exit")
		|| !ft_strcmp(token, "pwd"))
		return (true);
	return (false);
}

bool	is_redirect(t_token *cur)
{
	if (!cur)
		return (false);
	if (cur->type == TOKEN_REDIRECT_IN
		|| cur->type == TOKEN_REDIRECT_OUT
		|| cur->type == TOKEN_HEREDOC
		|| cur->type == TOKEN_APPEND)
		return (true);
	return (false);
}

bool	is_connection(t_token *cur)
{
	if (!cur)
		return (false);
	if (cur->type == TOKEN_CONJUNCTIONE
		|| cur->type == TOKEN_DISJUNCTIONE
		|| cur->type == TOKEN_PIPE)
		return (true);
	return (false);
}

bool	is_command(t_token *cur)
{
	if (!cur)
		return (false);
	if (cur->type == TOKEN_WORD
		|| is_redirect(cur))
		return (true);
	return (false);
}

t_tree_type	cmd_type(t_token *cur)
{
	if (is_builtin(cur->token))
		return (BUILTIN);
	return (COMMAND);
}
