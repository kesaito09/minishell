/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 21:50:47 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/22 20:44:40 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

t_token	*f_lstnew(char *token, t_token_type type)
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

int	append_list(t_token **list, t_token **cur)
{
	t_token	*node;

	node = f_lstnew((*cur)->token, TOKEN_WORD);
	if (!node)
		return (FAILUER);
	t_lstadd_back(list, node);
	*cur = (*cur)->next;
	return (SUCCESS);
}

int	append_redirect(t_token **file_list, t_token **cur)
{
	t_token			*new_file;
	t_token_type	ftype;
	char			*fname;

	ftype = (*cur)->type;
	*cur = (*cur)->next;
	if (!(*cur))
		return (FAILUER);
	if (ftype == TOKEN_HEREDOC)
		fname = heardoc((*cur)->token);
	else
		fname = ft_strdup((*cur)->token);
	if (!fname)
		return (FAILUER);
	new_file = f_lstnew(fname, ftype);
	free(fname);
	t_lstadd_back(file_list, new_file);
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
int	manage_append(t_tree *node, t_token **cur)
{
	if (is_redirect(*cur))
	{
		if (append_redirect(&node->file_list, cur) == FAILUER)
			return (free(node), FAILUER);
	}
	else if ( (*cur) && (*cur)->type == TOKEN_WORD && ft_strchr((*cur)->token, '='))
	{
		node->b_type = ENVP;
		if (append_list(&node->env_list, cur) == FAILUER)
			return (free(node), FAILUER);
	}
	else if ( (*cur) && (*cur)->type == TOKEN_WORD)
	{
		if (append_list(&node->arg_list, cur) == FAILUER)
			return (free(node), FAILUER);
	}
	return (SUCCESS);
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
		if (manage_append(node, cur) == FAILUER)
			return (free_tree_rec(node), NULL);
	return (node);
}
