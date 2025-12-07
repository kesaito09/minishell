/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getsize.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:54:28 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/07 02:18:17 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/parser.h"

// int	cmd_whole_size(t_token *lst)
// {
// 	t_token *tmp;
// 	int		i;

// 	tmp = lst;
// 	i = 0;
// 	while (tmp && tmp->type != PIPE)
// 	{
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	return (i);
// }

// int	redirect_size(t_token *lst)
// {
// 	t_token *tmp;
// 	int		i;

// 	tmp = lst;
// 	i = 0;
// 	while (tmp && tmp->type != PIPE)
// 	{
// 		if (TOKEN_REDIRECT_IN <= tmp->type && tmp->type <= TOKEN_APPEND)
// 			i++;
// 		tmp = tmp->next;
// 	}
// 	return (i);
// }

// int	cmd_size(int w, int r)
// {
// 	return (w - r);
// }

// int	count_cmd(t_token *lst)
// {
// 	int		i;
// 	t_token	*tmp;

// 	if (!lst)
// 		return (0);
// 	if (lst->type == PIPE)
// 		return (ERROR);
// 	tmp = lst;
// 	i = 1;
// 	while (tmp)
// 	{
// 		if (tmp->type == TOKEN_PIPE)
// 		{
// 			tmp = tmp->next;
// 			if (tmp && tmp->type != TOKEN_PIPE)
// 				i++;
// 			else
// 				return (ERROR);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (i);
// }

// t_token	*token_move(t_token *lst, int n)
// {
// 	int		i;
// 	t_token	*tmp;

// 	if (!lst)
// 		return (NULL);
// 	i = 0;
// 	tmp = lst;
// 	while (i <= n)
// 	{
// 		if (!tmp)
// 			return (NULL);
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	return (tmp);
// }
