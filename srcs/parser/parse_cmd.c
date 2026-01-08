/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 21:50:47 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/08 11:24:48 by kesaitou         ###   ########.fr       */
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
	new_file = t_lstnew(fname, 0);
	if (!new_file)
		return (free(fname), NULL);
	new_file->type = type;
	return (new_file);
}

int	append_redirect(t_token **file_list, t_token **cur, t_token *envp)
{
	t_token			*new_file;
	t_token_type	ftype;
	char			*fname;

	ftype = (*cur)->type;
	*cur = (*cur)->next;
	if (!(*cur))
		return (FAILUER);
	if (ftype == TOKEN_HEREDOC)
		fname = heardoc((*cur)->token, envp);
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

t_token	*token_word_last(t_token *cur)
{
	while (cur
		&& cur ->type == TOKEN_WORD
		&& cur ->next
		&& cur ->next ->type == TOKEN_WORD)
		cur = cur ->next;
	return (cur);
	//TOKEN_WORD以外ならエラーを出すべきかも
}

int	append_last_node(t_token **lst, t_token *new_lst)
{
	if (!lst || !new_lst)
		return (FAILUER);
	if (!*lst)
	{
		*lst = new_lst;
		return (SUCCESS);
	}
	t_lstadd_back(lst, new_lst);
	return (SUCCESS);
}

int	repoint_word_to_list(t_token **list, t_token **cur)
{
	t_token	*word_head;

	if (((*cur)->type != TOKEN_WORD))
		return (FAILUER);
	word_head = (*cur);
	*cur = (*cur)->next;
	word_head->next = NULL;
	if (append_last_node(list, word_head) == FAILUER)
		return (FAILUER);
	return (SUCCESS);
}

int	repoint_redirect_to_tree(t_tree *node, t_token **cur)
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
	if (append_last_node(&node->file_list, word) == FAILUER)
		return (FAILUER);
	op ->next = NULL;
	//free opする
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
	//かっこ閉じてない(error出す)
	subshell_node = tree_new(SUBSHELL);
	if (!subshell_node)
		return (NULL);
	subshell_node->left = parse_manage(cur, envp);
	if ((*cur)->type != TOKEN_PARENTHESIS_RIGHT)
		return (NULL);
	//かっこ閉じてない
	(*cur) = (*cur)->next;
	return (subshell_node);
}

int	manage_repoint(t_tree *node, t_token **cur)
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
		if (repoint_redirect_to_tree(node, cur) == FAILUER)
			return (FAILUER);
	}
	return (SUCCESS);
}

t_tree	*parse_command(t_token **cur, t_token *envp)
{
	t_tree	*node;

	if (!*cur || is_connection(*cur))
		return (NULL);
	//演算子が来たら構文エラーを出力する（やる
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
