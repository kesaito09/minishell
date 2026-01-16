/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 03:25:14 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/16 17:00:48 by kesaitou         ###   ########.fr       */
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

t_token	*get_sub_token(char **input)
{
	t_state	state;
	t_token	*node;
	int		n;

	state = STATE_GENERAL;
	n = 0;
	if (ft_strchr("'\"", **input))
		state = **input;
	if (state == STATE_GENERAL)
		n = word_len(*input, "'\"", NULL);
	else if (state == STATE_SQUOTE || state == STATE_DQUOTE)
		n = strchr_len(*input + 1, state) + 2;
	if (n <= 1)
		return (NULL);
	node = t_lstnew(ft_strndup(*input, n), free);
	*input += n;
	if (!node)
		return (NULL);
	node->type = what_type(state);
	return (node); 
}

t_token	*expand_dollar(t_token *input)
{	
	t_token	*node;
	t_token	*new;
	char	*str;
	int		len;

	str = input->token;
	node = NULL;
	while (*str)
	{
		len = strchr_len(str, '$');
		if (len < 0 && node && !*str)
			return (node);
		else if (len < 0 && !*str)
			return (input);
		else if (len < 0)
			len = ft_strlen(str);
		if (!len)
			len = count_varibles(str + 1) + 1;
		new = t_lstnew(ft_strndup(str, len), free);
		if (!new)
			return (t_lstclear(&node, free), NULL);
		str += len;
		t_lstadd_back(&node, new);
	}
	t_lstclear(&input, free);
	return (node);
}

t_token	*sub_token_lst(char *input)
{
	t_token	*lst;
	t_token	*new;
	char	*tmp;
	
	lst = NULL;
	while (*input)
	{
		new = get_sub_token(&input);
		if (!new)
			return (t_lstclear(&lst, free), NULL);
		if (new->type != SUB_TOKEN_GENERAL)
		{
			tmp = ft_substr(new->token, 1, ft_strlen(new->token) - 2);
			free(new->token);
			new->token = tmp;
		}
		if (new->type != SUB_TOKEN_SQUOTE)
			new = expand_dollar(new);
		t_lstadd_back(&lst, new);
	}
	return (lst);
}

int main(int ac, char **av)
{
	if (ac == 1)
		return (0);
	print_token(sub_token_lst(av[1]));
}
