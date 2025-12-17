/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 21:50:47 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/16 21:52:09 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

static t_file_type	check_ftype(t_token *cur)
{
	if (cur->type == TOKEN_REDIRECT_IN)
		return (INFILE);
	if (cur->type == TOKEN_REDIRECT_OUT)
		return (OUTFILE);
	if (cur->type == TOKEN_APPEND)
		return (APPEND);
	if (cur->type == TOKEN_HEREDOC)
		return (HEARDOC);
	return (NONE);
}
static int	append_redirect(t_tree *node, t_token **cur)
{
	t_flist		*new_file;
	t_file_type	ftype;
	char		*fname;

	ftype = check_ftype(*cur);
	*cur = (*cur)->next;
	if (!(*cur))
		return (FAILUER);
	if (ftype == HEARDOC)
	{
		fname = heardoc((*cur)->token);
		new_file = flist_new(ftype, fname);
	}
	else
	{
		fname = (*cur)->token;
		new_file = flist_new(ftype, fname);
	}
	if (!new_file)
		return (FAILUER);
	flist_add_back(&(node->flist), new_file);
	*cur = (*cur)->next;
	return (SUCCESS);
}

static int	append_argv(t_tree *node, t_token **cur)
{
	char	**new_argv;

	new_argv = ultimate_strjoin(node->argv, (*cur)->token);
	if (!new_argv)
		return (FAILUER);
	free_split(node->argv);
	node->argv = new_argv;
	*cur = (*cur)->next;
	return (SUCCESS);
}

t_tree	*parse_command(t_token **cur)
{
	t_tree	*node;

	if (!*cur || is_connection(*cur))
		return (NULL);
	node = tree_new(NULL, NULL, cmd_type(*cur));
	if (!node)
		return (NULL);
	while (is_command(*cur))
	{
		if (is_redirect(*cur))
			if (append_redirect(node, cur) == FAILUER)
				return (free(node), NULL);
		if ((*cur) && (*cur)->type == TOKEN_WORD)
			if (append_argv(node, cur) == FAILUER)
				return (free(node), NULL);
	}
	return (node);
}
