/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 03:25:14 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/08 10:01:03 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expander.h"

//char	*setup_ifs(t_token *envp)
//{
//	t_token	*var;

//	var = search_variable("IFS", envp);
//	if (!var)
//		return (ft_strdup(" \n\t"));
//	return (ft_strdup(var));
//}

//int	ft_strchr_len_set(char *str, char *set)
//{
//	int	len;

//	len = 0;
//	if (!str)
//		return (-1);
//	while (str[len] && ft_strchr(set, str[len]))
//		len++;
//	return (len);
//}

//static void	skip_set(char **str, char *set)
//{
//	while (**str && ft_strchr(set, **str))
//		(*str)++;
//}

//t_token	*string_to_tlist(char *sub_token, char *set)
//{
//	t_token	*new_tlist;
//	char	*new_token;
//	int		len;

//	new_tlist = NULL;
//	len = 0;
//	while (*sub_token)
//	{
//		len = ft_strchr_len_set(set, *sub_token);
//		if (len < 0)
//			new_token = ft_strdup(sub_token);
//		else if (len == 0)
//			skip_set(&sub_token, set);
//		else
//			new_token = ft_strndup(sub_token, len);
//		if (!new_token)
//			return (FAILUER);



//	}




//}

//t_token	*split_sub_token(t_token *sub_token, char *set)
//{




//}

//t_token	*split_to_tlist(t_token *token, char *set)
//{
//	while (token)
//	{
//		if (token->sub_token->type != SUB_TOKEN_GENERAL)
//		{
//			token = token->next;
//			continue ;
//		}
//	}
//}