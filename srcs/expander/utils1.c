/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:27:47 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/17 20:36:49 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expander.h"

int	envlen(char *av)
{
	int	len;

	len = 0;
	if (av[0] == '?')
		return (1);
	while (av[len] && !is_env_delimiter(av[len]))
		len++;
	return (len);
}

int	strchr_len(char *str, int c)
{
	char	*ptr;

	ptr = ft_strchr(str, c);
	if (!ptr)
		return (-1);
	return ((int)(ptr - str));
}

void	deep_token_clear(t_token *node)
{
	t_token	*next_node;

	while (node)
	{
		next_node = node->next;
		if (node->sub_token)
			t_lstclear(&node->sub_token, free);
		free(node->token);
		free(node);
		node = next_node;
	}
}
