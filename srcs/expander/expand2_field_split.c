/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2_field_split.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:15:22 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/08 09:51:01 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expander.h"

t_token	*string_to_tlist(char *token, char *set, t_token_type type)
{
	t_token	*new_tlist;
	t_token	*new_node;
	char	*new_token;
	int		len;

	new_tlist = NULL;
	while (*token)
	{
		skip_set(&token, set);
		if (!*token)
			break ;
		len = ft_strchr_len_set(token, set);
		new_token = ft_strndup(token, len);
		if (!new_token)
			return (NULL);
		new_node = t_lstnew(new_token, type);
		if (!new_node)
			return (NULL);
		t_lstadd_back(&new_tlist, new_node);
		token += len;
	}
	return (new_tlist);
}

int	merge_tlist(t_token **sub_token, char *set, t_token_type type)
{
	t_token	*new_lst;
	t_token	*cur;
	t_token	*next;
	int		flag;

	if (!sub_token || !set)
		return (FAILUER);
	flag = PASS;
	while (*sub_token)
	{
		cur = *sub_token;
		if (cur->type != SUB_TOKEN_DOLLAR)
		{
			sub_token = &cur->next;
			continue ;
		}
		flag = SUCCESS;
		next = cur->next;
		new_lst = string_to_tlist(cur->token, set, type);
		if (!new_lst)
			return (FAILUER);
		*sub_token = new_lst;
		t_lstlast(new_lst)->next = next;
		free(cur->token);
		free(cur);
		sub_token = &t_lstlast(new_lst)->next;
	}
	return (flag);
}

int	split_token_list(t_token **token_list, t_token *envp, t_token_type type)
{
	char	*new_token;
	char	*ifs;
	int		flag;

	ifs = setup_ifs(envp);
	if (!ifs)
		return (FAILUER);
	while (*token_list)
	{
		flag = merge_tlist(&(*token_list)->sub_token, ifs, type);
		if (flag == FAILUER)
			return (FAILUER);
		else if (flag == SUCCESS)
		{
			new_token = join_sub_token((*token_list) ->sub_token);
			if (!new_token)
				return (FAILUER);
			free((*token_list) ->token);
			(*token_list) ->token = new_token;	
		}						
		token_list = &(*token_list)->next;
	}
	return (SUCCESS);
}

/*
	SUB_TOKEN_DOLLERが来たときだけ、展開する
	サブトークンのタイプが11のときだけifsで分割処理する


	ダブルクォートはIFS展開しない
	サブトークンを展開する。



*/