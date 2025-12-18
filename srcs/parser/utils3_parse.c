/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:13:11 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/16 21:55:36 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/execution.h"

t_tree_type	cmd_type(t_token *cur)
{
	if (is_builtin(cur->token))
		return (MY_COMMAND);
	return (COMMAND);
}

int	count_arr_elem(char **s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	**ultimate_strjoin(char **argv, char *new)
{
	char	**new_argv;
	int		arr_elem;
	int		i;

	if (!new)
		return (NULL);
	arr_elem = count_arr_elem(argv);
	new_argv = ft_calloc(arr_elem + 2, sizeof(char **));
	if (!new_argv)
		return (NULL);
	i = 0;
	while (i < arr_elem)
	{
		new_argv[i] = ft_strdup(argv[i]);
		if (!new_argv[i])
			return (free_split(new_argv), NULL);
		i++;
	}
	new_argv[i] = ft_strdup(new);
	if (!new_argv[i])
		return (free_split(new_argv), NULL);
	return (new_argv);
}
