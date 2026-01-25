/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 21:50:47 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/25 09:10:57 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

static t_tree	*parse_subshell(t_token **cur, t_shared_info *info);
static int		manage_repoint(t_tree *node, t_token **cur, t_shared_info *inf);
static int		repoint_word_to_list(t_token **list, t_token **cur);
static int		repoint_redirect_to_list(t_token **list, t_token **cur);

t_tree	*parse_command(t_token **cur, t_shared_info *info)
{
	t_tree	*branch;

	if (!*cur)
		return (syntax_error_msg(NULL), NULL);
	if (is_connection(*cur))
		return (syntax_error_msg((*cur)->token), NULL);
	if ((*cur) && ((*cur)->type == TOKEN_PARENTHESIS_RIGHT))
		return (syntax_error_msg((*cur)->token), NULL);
	if ((*cur) && ((*cur)->type == TOKEN_PARENTHESIS_LEFT))
		return (parse_subshell(cur, info));
	branch = tree_new(COMMAND);
	if (!branch)
		return (NULL);
	while (*cur && is_command(*cur))
	{
		if (manage_repoint(branch, cur, info) == FAILUER)
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
		if (repoint_word_to_list(&branch->env_list, cur) == FAILUER)
			return (FAILUER);
	}
	else if ((*cur) && (*cur)->type == TOKEN_WORD)
	{
		if (repoint_word_to_list(&branch->arg_list, cur) == FAILUER)
			return (FAILUER);
	}
	else if ((*cur) && is_redirect(*cur))
	{
		if ((*cur)->type == TOKEN_HEREDOC && (*cur)->next)
			(*cur)->next->token = heardoc((*cur)->next->token, info);
		if (repoint_redirect_to_list(&branch->file_list, cur) == FAILUER)
			return (FAILUER);
	}
	return (SUCCESS);
}

static int	repoint_word_to_list(t_token **list, t_token **cur)
{
	t_token	*word_head;

	if (!cur || !*cur || ((*cur)->type != TOKEN_WORD))
		return (FAILUER);
	word_head = (*cur);
	*cur = (*cur)->next;
	word_head->next = NULL;
	t_lstadd_back(list, word_head);
	return (SUCCESS);
}

static int	repoint_redirect_to_list(t_token **list, t_token **cur)
{
	t_token			*op;
	t_token			*word;
	t_token			*next;

	if (!cur || !*cur || !(is_redirect(*cur)))
		return (FAILUER);
	op = (*cur);
	word = op ->next;
	if (!word)
		return (syntax_error_msg("newline"), FAILUER);
	if (word->type != TOKEN_WORD)
		return (syntax_error_msg(word->token), FAILUER);
	word ->type = op ->type;
	next = word ->next;
	word ->next = NULL;
	t_lstadd_back(list, word);
	t_lstdelone(op, free);
	(*cur) = next;
	return (SUCCESS);
}

static t_tree	*parse_subshell(t_token **cur, t_shared_info *info)
{
	t_tree	*subshell_node;

	if (!cur || !*cur)
		return (syntax_error_msg("newline"), NULL);
	free_and_skip_one(cur);
	if (!(*cur))
		return (syntax_error_msg("newline"), NULL);
	if ((*cur)->type == TOKEN_PARENTHESIS_RIGHT)
		return (syntax_error_msg(")"), NULL);
	subshell_node = tree_new(SUBSHELL);
	if (!subshell_node)
		return (NULL);
	subshell_node->left = parse_manage(cur, info);
	if (!subshell_node ->left)
		return (free_tree_rec(&subshell_node), NULL);
	if (!*cur)
		return (syntax_error_msg("newline"),
			free_tree_rec(&subshell_node), NULL);
	if ((*cur)->type != TOKEN_PARENTHESIS_RIGHT)
		return (syntax_error_msg((*cur)->token),
			free_tree_rec(&subshell_node), NULL);
	free_and_skip_one(cur);
	return (subshell_node);
}
