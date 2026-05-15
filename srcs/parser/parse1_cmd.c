/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 21:50:47 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/15 16:01:37 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

static int	consume_command_tokens(t_tree *branch, t_token **cur,
				t_shared_info *info);
static int	consume_redirect_tokens(t_tree *branch, t_token **cur,
				t_shared_info *info);
static void	finalize_type(t_tree *branch);

t_tree	*parse_command(t_token **cur, t_shared_info *info)
{
	t_tree	*branch;

	if (!*cur)
		return (err_syntax(info, NULL), NULL);
	if (is_connection(*cur) || (*cur)->type == TOKEN_PARENTHESIS_RIGHT)
		return (err_syntax(info, (*cur)->token), NULL);
	if ((*cur)->type == TOKEN_PARENTHESIS_LEFT)
		branch = parse_subshell(cur, info);
	else
		branch = tree_new(COMMAND);
	if (!branch)
		return (NULL);
	if (consume_command_tokens(branch, cur, info) == FAILURE)
		return (free_tree_rec(&branch), NULL);
	finalize_type(branch);
	return (branch);
}

static int	consume_command_tokens(t_tree *branch, t_token **cur,
		t_shared_info *info)
{
	while (*cur && is_command(*cur))
	{
		if (branch->b_type == SUBSHELL && !is_redirect(*cur))
			return (err_syntax(info, (*cur)->token), FAILURE);
		if (is_valid_arg((*cur)->token) && !branch->arg_list)
			splice_to_list(&branch->env_list, cur);
		else if ((*cur)->type == TOKEN_WORD)
			splice_to_list(&branch->arg_list, cur);
		else if (consume_redirect_tokens(branch, cur, info) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

static int	consume_redirect_tokens(t_tree *branch, t_token **cur,
		t_shared_info *info)
{
	t_token	*op;
	t_token	*word;

	op = *cur;
	word = op->next;
	if (!word)
		return (err_syntax(info, "newline"), FAILURE);
	if (op->type == TOKEN_HEARDOC)
	{
		word->token = heardoc(word->token, branch, info, *cur);
		if (!word->token)
			return (FAILURE);
	}
	if (word->type != TOKEN_WORD)
		return (err_syntax(info, word->token), FAILURE);
	word->type = op->type;
	*cur = word;
	t_lstdelone(op, free);
	splice_to_list(&branch->file_list, cur);
	return (SUCCESS);
}

static void	finalize_type(t_tree *branch)
{
	if (!branch->arg_list && branch->env_list)
		branch->b_type = ENVP;
	if (branch->arg_list)
		branch->b_type = cmd_type(branch->arg_list);
}
