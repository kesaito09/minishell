/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2_subshell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 00:00:00 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/07 08:28:49 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

static int	validate_subshell_open(t_token **cur, t_shared_info *info);
static int	validate_subshell_close(t_token **cur, t_shared_info *info);

t_tree	*parse_subshell(t_token **cur, t_shared_info *info)
{
	t_tree	*node;

	if (validate_subshell_open(cur, info) == FAILURE)
		return (NULL);
	node = tree_new(SUBSHELL);
	if (!node)
		return (NULL);
	node->left = parse_left_join(cur, info, OP_LOGICAL);
	if (!node->left || validate_subshell_close(cur, info) == FAILURE)
		return (free_tree_rec(&node), NULL);
	return (node);
}

static int	validate_subshell_open(t_token **cur, t_shared_info *info)
{
	if (!cur || !*cur)
		return (err_syntax(info, "newline"), FAILURE);
	free_and_skip_one(cur);
	if (!*cur)
		return (err_syntax(info, "newline"), FAILURE);
	if ((*cur)->type == TOKEN_PARENTHESIS_RIGHT)
		return (err_syntax(info, ")"), FAILURE);
	return (SUCCESS);
}

static int	validate_subshell_close(t_token **cur, t_shared_info *info)
{
	if (!*cur)
		return (err_syntax(info, "newline"), FAILURE);
	if ((*cur)->type != TOKEN_PARENTHESIS_RIGHT)
		return (err_syntax(info, (*cur)->token), FAILURE);
	free_and_skip_one(cur);
	return (SUCCESS);
}
