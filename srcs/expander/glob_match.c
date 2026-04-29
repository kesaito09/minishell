/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob_match.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 01:40:49 by natakaha          #+#    #+#             */
/*   Updated: 2026/04/19 15:58:31 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"
#include "../../includes/expander.h"

static bool	glob_match(t_token *sub, size_t pos, const char *file);
static bool	match_wildcard(t_token *sub, size_t pos, const char *file);

int	search_file(t_token *sub_token, char *file)
{
	if (!sub_token || !file)
		return (false);
	return (glob_match(sub_token, 0, file));
}

static bool	glob_match(t_token *sub, size_t pos, const char *file)
{
	while (sub && sub->token[pos] == '\0')
	{
		sub = sub->next;
		pos = 0;
	}
	if (!sub)
		return (*file == '\0');
	if (sub->type == SUB_TOKEN_GENERAL && sub->token[pos] == '*')
		return (match_wildcard(sub, pos, file));
	if (*file != sub->token[pos])
		return (false);
	return (glob_match(sub, pos + 1, file + 1));
}

static bool	match_wildcard(t_token *sub, size_t pos, const char *file)
{
	while (sub->token[pos] == '*')
		pos++;
	if (glob_match(sub, pos, file))
		return (true);
	if (*file == '\0')
		return (false);
	return (match_wildcard(sub, pos - 1, file + 1));
}
