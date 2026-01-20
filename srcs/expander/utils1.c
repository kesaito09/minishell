/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:27:47 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/21 04:56:20 by natakaha         ###   ########.fr       */
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

char	*split_join(char **argv)
{
	char	*str;
	char	*trash;
	int		i;

	i = 0;
	if (!argv || !*argv)
		return (NULL);
	str = argv[i++];
	while (argv[i])
	{
		trash = str;
		str = ft_strjoin(str, argv[i]);
		free(trash);
		if (!str)
			return (NULL);
		i++;
	}
	return (str);
}

char	*token_join(t_token *lst)
{
	char	**argv;

	argv = token_argv(lst);
	if (!argv)
		return (NULL);
	return (split_join(argv));
}

char	*expand_join(char *input, t_token *envp, t_token_type type)
{
	t_token	*node;

	node = get_sub_token(input, envp, type);
	if (!node)
		return (NULL);
	return (token_join(node));
}
