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

static int	is_redirect(t_token *cur)
{
	return (cur->type == TOKEN_REDIRECT_IN || cur->type == TOKEN_REDIRECT_OUT
		|| cur->type == TOKEN_HEREDOC || cur->type == TOKEN_APPEND);
}

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
static void	append_redirect(t_tree *node, t_token **curr)
{
	t_flist		*new_file;
	t_file_type	ftype;
	char		*fname;

	ftype = check_ftype(*curr);
	*curr = (*curr)->next;
	if ((*curr)->type == TOKEN_EOF)
		return ;
	fname = (*curr)->token;
	new_file = flist_new(ftype, fname);
	flist_add_back(&(node->flist), new_file);
	*curr = (*curr)->next;
}

static void	append_argv(t_tree *node, t_token **curr)
{
	char	**new_argv;

	new_argv = ultimate_strjoin(node->argv, (*curr)->token);
	if (!new_argv)
		return ;
	free_split(node->argv);
	node->argv = new_argv;
	*curr = (*curr)->next;
}

t_tree	*parse_command(t_token **cur)
{
	t_tree	*node;

	if ((*cur)->type == TOKEN_PIPE
		|| (*cur)->type == TOKEN_EOF
		|| (*cur)->type == TOKEN_CONJUNCTIONE
		|| (*cur)->type == TOKEN_DISJUNCTIONE)
		return (NULL);
	node = tree_new(NULL, NULL, cmd_type(*cur));
	while (*cur
			&& (*cur)->type != TOKEN_PIPE
			&& (*cur)->type != TOKEN_EOF
			&& (*cur)->type != TOKEN_CONJUNCTIONE
			&& (*cur)->type != TOKEN_DISJUNCTIONE)
	{
		if (is_redirect(*cur))
			append_redirect(node, cur);
		else
			append_argv(node, cur);
	}
	return (node);
}