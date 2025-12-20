/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 21:50:47 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/20 12:41:34 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"


static t_token	*treat_heardoc(char *token)
{
	char	*fname;
	t_token	*new_file;

	fname = heardoc(token);
	if (!fname)
			return (NULL);
	new_file = t_lstnew(fname);
	if (!new_file)
		return (free(fname), NULL);
	new_file->type = TOKEN_HEREDOC;
	return (new_file);
}

static	t_token	*f_lstnew(char *token, t_token_type type)
{
	char	*fname;
	t_token	*new_file;

	fname = ft_strdup(token);
	if (!fname)
		return (NULL);
	new_file = t_lstnew(fname);
	if (!new_file)
		return (free(fname), NULL);
	new_file->type = type;
	return (new_file);
}

static int	append_redirect(t_tree *branch, t_token **cur)
{
	t_token			*new_file;
	t_token_type	ftype;

	ftype = (*cur)->type;
	*cur = (*cur)->next;
	if (!(*cur))
		return (FAILUER);
	if (ftype == TOKEN_HEREDOC)
	{
		new_file = treat_heardoc((*cur)->token);
		if (!new_file)
			return (FAILUER);
	}
	else
	{
		new_file = f_lstnew((*cur)->token, ftype);
		if (!new_file)
			return (FAILUER);
	}
	t_lstadd_back(&(branch->file_list), new_file);
	*cur = (*cur)->next;
	return (SUCCESS);
}

static t_tree	*parse_subshell(t_token **cur)
{
	t_tree *subshell_node;

	(*cur) = (*cur) ->next;
	if (!(*cur))
		return (NULL);
	subshell_node = tree_new(SUBSHELL);
	if (!subshell_node)
		return (NULL);
	subshell_node ->left = parse_manage(cur);
	if ((*cur) ->type != TOKEN_PARENTHESIS_RIGHT)
		return (NULL);
	(*cur) = (*cur) ->next;
	return (subshell_node);
}

t_tree	*parse_command(t_token **cur)
{
	t_tree	*node;

	if (!*cur || is_connection(*cur))
		return (NULL);
	if ((*cur) && ((*cur) ->type == TOKEN_PARENTHESIS_LEFT))
		return (parse_subshell(cur));
	node = tree_new(cmd_type(*cur));
	if (!node)
		return (NULL);
	while (is_command(*cur))
	{
		if (is_redirect(*cur))
		{
			if (append_redirect(node, cur) == FAILUER)
				return (free(node), NULL);
		}
		else if ( (*cur) && (*cur) ->type == TOKEN_WORD)
		{
			if (append_token(node, cur) == FAILUER)
				return (free(node), NULL);
		}
	}
	return (node);
}
