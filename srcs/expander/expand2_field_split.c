/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2_field_split.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:15:22 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/10 20:56:19 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expander.h"

static int	append_field_token(t_token **list, char *begin, size_t length, t_token_type type)
{
	char	*field_text;
	t_token	*field_node;

	field_text = ft_strndup(begin, (int)length);
	if (!field_text)
		return (FAILUER);
	field_node = t_lstnew(field_text, type);
	if (!field_node)
		return (free(field_text), FAILUER);
	t_lstadd_back(list, field_node);
	return (SUCCESS);
}

int	string_to_tlist_whitespace(char *input, char *ifs,
										t_token_type type, t_token **new_list)
{
	char		*cur;
	char		*field_begin;
	t_token		*result_list;

	if (!new_list)
		return (FAILUER);
	*new_list = NULL;
	if (!input || !ifs)
		return (SUCCESS);
	cur = input;
	result_list = NULL;
	while (*cur)
	{
		while (*cur && is_delimiter_ifs(ifs, *cur))
			cur++;
		if (!*cur)
			break;
		field_begin = cur;
		cur = scan_until_delimiter(cur, ifs);
		if (append_field_token(&result_list, field_begin,
				(size_t)(cur - field_begin), type) == FAILUER)
			return (free_token_list(result_list), FAILUER);
	}
	*new_list = result_list;
	return (SUCCESS);
}

int	string_to_tlist_nonwhitespace( char *input,  char *ifs,
											t_token_type type, t_token **new_list)
{
	char		*cur;
	char		*field_begin;
	t_token		*result_list;
	int			need_trailing_empty;

	if (!new_list)
		return (FAILUER);
	*new_list = NULL;
	if (!input || !ifs)
		return (SUCCESS);
	cur = skip_ifs_whitespace(input, ifs);
	result_list = NULL;
	need_trailing_empty = 0;
	while (1)
	{
		if (need_trailing_empty && append_field_token(&result_list, cur, 0, type) == FAILUER)
			return (free_token_list(result_list), FAILUER);
		if (need_trailing_empty)
			break;
		field_begin = cur;
		cur = scan_until_delimiter(cur, ifs);
		if (cur > field_begin && append_field_token(&result_list, field_begin,
				(size_t)(cur - field_begin), type) == FAILUER)
			return (free_token_list(result_list), FAILUER);
		else if (cur == field_begin && *cur && is_delimiter_ifs(ifs, *cur)
			&& !is_ifs_whitespace(*cur)
			&& append_field_token(&result_list, cur, 0, type) == FAILUER)
			return (free_token_list(result_list), FAILUER);
		if (!*cur)
			break;
		if (is_delimiter_ifs(ifs, *cur) && is_ifs_whitespace(*cur))
			cur = consume_whitespace(cur, ifs, &need_trailing_empty);
		else
			cur = consume_one_nonwhitespace_delimiter(cur, ifs, &need_trailing_empty);
	}
	*new_list = result_list;
	return (SUCCESS);
}

int	string_to_tlist_ifs(char *input, char *ifs, t_token_type type, t_token **new_list)
{
	if (!new_list)
		return (FAILUER);
	*new_list = NULL;
	if (!input || !ifs)
		return (SUCCESS);
	if (is_only_whitespace(ifs))
		return (string_to_tlist_whitespace(input, ifs, type, new_list));
	return (string_to_tlist_nonwhitespace(input, ifs, type, new_list));
}

int	split_token_list(t_token **token_list, t_token *envp, t_token_type type)
{
	char	*ifs;
	t_token	*current_node;
	t_token	*new_list;
	t_token	*last_node;

	(void)type;
	if (!token_list)
		return (FAILUER);
	ifs = setup_ifs(envp);
	if (!ifs)
		return (FAILUER);
	while (*token_list)
	{
		current_node = *token_list;
		if (string_to_tlist_ifs(current_node->token, ifs, current_node->type, &new_list) == FAILUER)
			return (free(ifs), FAILUER);
		if (!new_list)
		{
			*token_list = current_node->next;
			free_token_list(current_node->sub_token);
			free(current_node->token);
			free(current_node);
			continue;
		}
		last_node = t_lstlast(new_list);
		last_node->next = current_node->next;
		*token_list = new_list;
		free_token_list(current_node->sub_token);
		free(current_node->token);
		free(current_node);
		token_list = &last_node->next;
	}
	free(ifs);
	return (SUCCESS);
}



// int	split_token_list(t_token **token_list, t_token *envp, t_token_type type)
// {
// 	char	*new_token;
// 	char	*ifs;
// 	int		flag;

// 	ifs = setup_ifs(envp);
// 	if (!ifs)
// 		return (FAILUER);
// 	while (*token_list)
// 	{
// 		flag = merge_tlist(&(*token_list)->sub_token, ifs, type);
// 		if (flag == FAILUER)
// 			return (FAILUER);
// 		else if (flag == SUCCESS)
// 		{
// 			new_token = join_sub_token((*token_list) ->sub_token);
// 			if (!new_token)
// 				return (FAILUER);
// 			free((*token_list) ->token);
// 			(*token_list) ->token = new_token;
// 		}
// 		token_list = &(*token_list)->next;
// 	}
// 	return (SUCCESS);
// }

//	tmp = *token_list;
//	while (tmp)
//	{
//		new_sub_token = split_sub_token(tmp->sub_token, envp);
//		if (!new_sub_token)
//			return (FAILUER);
//		//ここで繋げる
//		tmp = tmp->next;
//	}
//	return (SUCCESS);
//}

///*
//	SUB_TOKEN_DOLLERが来たときだけ、展開する
//	サブトークンのタイプが11のときだけifsで分割処理する

//	ダブルクォートはIFS展開しない
//	サブトークンを展開する。

//*/