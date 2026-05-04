/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 21:50:47 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/01 17:31:56 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

static t_tree	*parse_subshell(t_token **cur, t_shared_info *info);
static int		manage_repoint(t_tree *node, t_token **cur, t_shared_info *inf);
static int		repoint_word_to_list(t_token **list, t_token **cur);
static int		repoint_redirect_to_list(t_token **list, t_token **cur,
					t_shared_info *info);

t_tree	*parse_command(t_token **cur, t_shared_info *info)
{
	t_tree	*branch;

	if (!*cur)
		return (err_syntax(info, NULL), NULL);
	if (is_connection(*cur) || ((*cur)->type == TOKEN_PARENTHESIS_RIGHT))
		return (err_syntax(info, (*cur)->token), NULL);
	if ((*cur) && ((*cur)->type == TOKEN_PARENTHESIS_LEFT))
		branch = parse_subshell(cur, info);
	else
		branch = tree_new(COMMAND);
	if (!branch)
		return (NULL);
	while (*cur && is_command(*cur))
	{
		if (branch->b_type == SUBSHELL && !is_redirect(*cur))
			return (err_syntax(info, (*cur)->token), free_tree_rec(&branch),
				NULL);
		if (manage_repoint(branch, cur, info) == FAILURE)
			return (free_tree_rec(&branch), NULL);
	}
	if (!branch->arg_list && branch->env_list)
		branch->b_type = ENVP;
	if (branch->arg_list)
		branch->b_type = cmd_type(branch->arg_list);
	return (branch);
}

static int	manage_repoint(t_tree *branch, t_token **cur, t_shared_info *info)
{
	if (is_valid_arg((*cur)->token) && !branch->arg_list)
	{
		if (repoint_word_to_list(&branch->env_list, cur) == FAILURE)
			return (FAILURE);
	}
	else if ((*cur) && (*cur)->type == TOKEN_WORD)
	{
		if (repoint_word_to_list(&branch->arg_list, cur) == FAILURE)
			return (FAILURE);
	}
	else if ((*cur) && is_redirect(*cur))
	{
		if ((*cur)->type == TOKEN_HEARDOC && (*cur)->next)
		{
			(*cur)->next->token = heardoc((*cur)->next->token, branch, info);
			if (!(*cur)->next->token)
				return (FAILURE);
		}
		if (repoint_redirect_to_list(&branch->file_list, cur, info) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	repoint_word_to_list(t_token **list, t_token **cur)
{
	t_token	*word_head;

	if (!cur || !*cur || ((*cur)->type != TOKEN_WORD))
		return (FAILURE);
	word_head = (*cur);
	*cur = (*cur)->next;
	word_head->next = NULL;
	t_lstadd_back(list, word_head);
	return (SUCCESS);
}

static int	repoint_redirect_to_list(t_token **list, t_token **cur,
		t_shared_info *info)
{
	t_token	*op;
	t_token	*word;
	t_token	*next;

	if (!cur || !*cur || !(is_redirect(*cur)))
		return (FAILURE);
	op = (*cur);
	word = op->next;
	if (!word)
		return (err_syntax(info, "newline"), FAILURE);
	if (word->type != TOKEN_WORD)
		return (err_syntax(info, word->token), FAILURE);
	word->type = op->type;
	next = word->next;
	word->next = NULL;
	t_lstadd_back(list, word);
	t_lstdelone(op, free);
	(*cur) = next;
	return (SUCCESS);
}

static t_tree	*parse_subshell(t_token **cur, t_shared_info *info)
{
	t_tree	*subshell_node;

	if (!cur || !*cur)
		return (err_syntax(info, "newline"), NULL);
	free_and_skip_one(cur);
	if (!(*cur))
		return (err_syntax(info, "newline"), NULL);
	if ((*cur)->type == TOKEN_PARENTHESIS_RIGHT)
		return (err_syntax(info, ")"), NULL);
	subshell_node = tree_new(SUBSHELL);
	if (!subshell_node)
		return (NULL);
	subshell_node->left = parse_left_join(cur, info, OP_LOGICAL);
	if (!subshell_node->left)
		return (free_tree_rec(&subshell_node), NULL);
	if (!*cur)
		return (err_syntax(info, "newline"), free_tree_rec(&subshell_node),
			NULL);
	if ((*cur)->type != TOKEN_PARENTHESIS_RIGHT)
		return (err_syntax(info, (*cur)->token), free_tree_rec(&subshell_node),
			NULL);
	free_and_skip_one(cur);
	return (subshell_node);
}
