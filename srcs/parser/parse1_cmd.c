/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 21:50:47 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/17 20:29:17 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

static t_tree	*parse_subshell(t_token **cur, t_token *envp);
static int		manage_repoint(t_tree *node, t_token **cur);
static int		repoint_word_to_list(t_token **list, t_token **cur);
static int		repoint_redirect_to_list(t_token **list, t_token **cur);
static t_tree	*parse_subshell(t_token **cur, t_token *envp);


t_tree	*parse_command(t_token **cur, t_token *envp)
{
	t_tree	*node;

	if (!*cur || is_connection(*cur))
		return (NULL);
	if ((*cur) && ((*cur)->type == TOKEN_PARENTHESIS_LEFT))
		return (parse_subshell(cur, envp));
	node = tree_new(cmd_type(*cur));
	if (!node)
		return (NULL);
	while (is_command(*cur))
	{
		if (manage_repoint(node, cur) == FAILUER)
			return (free_tree_rec(node), NULL);
	}
	return (node);
}

static int	manage_repoint(t_tree *node, t_token **cur)
{
	if (is_valid_arg((*cur)->token) && !node->arg_list)
	{
		node->b_type = ENVP;
		if (repoint_word_to_list(&node->env_list, cur) == FAILUER)
			return (free(node), FAILUER);
	}
	else if ((*cur) && (*cur)->type == TOKEN_WORD)
	{
		if (repoint_word_to_list(&node->arg_list, cur) == FAILUER)
			return (free(node), FAILUER);
	}
	else if ((*cur) && is_redirect(*cur))
	{
		if (repoint_redirect_to_list(&node->file_list, cur) == FAILUER)
			return (FAILUER);
	}
	return (SUCCESS);
}

static int	repoint_word_to_list(t_token **list, t_token **cur)
{
	t_token	*word_head;

	if (((*cur)->type != TOKEN_WORD))
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

	if (!(is_redirect(*cur)))
		return (FAILUER);
	op = (*cur);
	word = op ->next;
	if (!word || word ->type != TOKEN_WORD)
	{
		ft_putendl_fd("minishell: syntax error near unexpected token", 2);
		return (FAILUER);
	}
	word ->type = op ->type;
	next = word ->next;
	word ->next = NULL;
	t_lstadd_back(list, word);
	op ->next = NULL;
	(*cur) = next;
	return (SUCCESS);
}

static t_tree	*parse_subshell(t_token **cur, t_token *envp)
{
	t_tree	*subshell_node;

	if (!cur)
		return (NULL);
	(*cur) = (*cur)->next;
	if (!(*cur))
		return (NULL);
	subshell_node = tree_new(SUBSHELL);
	if (!subshell_node)
		return (NULL);
	subshell_node->left = parse_manage(cur, envp);
	if ((*cur)->type != TOKEN_PARENTHESIS_RIGHT)
		return (NULL);
	(*cur) = (*cur)->next;
	return (subshell_node);
}
