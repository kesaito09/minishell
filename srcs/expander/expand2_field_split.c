/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2_field_split.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:15:22 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/08 04:17:02 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expander.h"


// int	copy_first_pointer(t_token **token_list, t_token *new_token_list)
// {
// 	t_token	*cur;

// 	cur = *token_list;
// 	cur->next = new_token_list->next;
// 	cur->sub_token = new_token_list->sub_token;
// }



// t_token	*expand_sub_token(char *sub_token, t_token *envp)
// {
// 	t_token	*tmp;
// 	char	*new_token;
// 	char	*ifs;
// 	int		dup_len;
// 	char	*ifs;

// 	ifs = setup_ifs(envp);
// 	if (!ifs)
// 		return (NULL);
// 	while (*sub_token)
// 	{
// 		dup_len = ft_strchr_set(sub_token, ifs);
// 		if (dup_len < 0)
// 			return (NULL);
// 		new_token = ft_strndup(sub_token, dup_len);
// 		if (!new_token)
// 			return (NULL);
		
// 	}
// }

// t_token	*split_sub_token(t_token *sub_token, t_token *envp)
// {
// 	t_token	*new_sub;

// 	while (sub_token)
// 	{
// 		if (sub_token->type != SUB_TOKEN_GENERAL)
// 		{
// 			sub_token = sub_token->next;
// 			continue ;
// 		}
// 		sub_token 
// 	}
// }

// int	field_spliting(t_token **token_list, t_token *envp)
// {
// 	t_token	*tmp;
// 	t_token	*new_sub_token;

// 	tmp = *token_list;
// 	while (tmp)
// 	{
// 		new_sub_token = split_sub_token(tmp->sub_token, envp);
// 		if (!new_sub_token)
// 			return (FAILUER);
// 		//ここで繋げる
// 		tmp = tmp->next;
// 	}
// 	return (SUCCESS);
// }

/*
	SUB_TOKEN_DOLLERが来たときだけ、展開する
	サブトークンのタイプが11のときだけifsで分割処理する


	ダブルクォートはIFS展開しない
	サブトークンを展開する。



*/