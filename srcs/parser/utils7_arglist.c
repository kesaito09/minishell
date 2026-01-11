/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7_arglist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 02:58:10 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/08 18:08:19 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

char	**token_argv(t_token *node)
{
	char	**argv;
	int		i;
	t_token	*tmp;

	ft_putendl_fd(node->next->token, 2);
	i = t_lstsize(node);
	ft_putendl_fd(node->next->token, 2);
	argv = (char **)ft_calloc(i + 1, sizeof(char *));
	ft_putendl_fd(node->next->token, 2);
	if (!argv)
		return (NULL);
	ft_putendl_fd(node->next->token, 2);
	tmp = node;
	i = 0;
	while (tmp)
	{
		argv[i] = ft_strdup(tmp->token);
		if (!argv[i])
			return (free_split(argv), NULL);
		i++;
		tmp = tmp->next;
	}
	return (argv);
}

t_token	*argv_token(char **argv)
{
	t_token *node;
	t_token *lst;
	int i;

	i = 0;
	lst = NULL;
	while (argv[i])
	{
		node = f_lstnew(argv[i], TOKEN_WORD);
		if (!node)
			return (t_lstclear(&lst, free), NULL);
		t_lstadd_back(&lst, node);
		i++;
	}
	return (lst);
}
