/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:27:47 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/18 10:44:35 by natakaha         ###   ########.fr       */
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

char	*split_join(char **argv)
{
	char	*str;
	char	*trash;

	if (!argv || !*argv)
		str = *argv;
	while (++*argv)
	{
		trash = str;
		str = ft_strjoin(str, *argv);
		free(trash);
	}
	return (str);
}

char	*expand_join(char *input, t_token *envp)
{
	t_token	*node;
	char	**argv;
	char	*str;

	node = get_sub_token(input, envp);
	if (!node)
		return (NULL);
	argv = token_argv(node);
	free(node);
	if (!argv)
		return (NULL);
	str = split_join(argv);
	free(argv);
	if (!str)
		return (NULL);
	return (str);
}
