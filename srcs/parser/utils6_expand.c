/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-12-17 15:55:39 by natakaha          #+#    #+#             */
/*   Updated: 2025-12-17 15:55:39 by natakaha         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

char	*env_is(const char *arg, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_argcmp(arg, envp[i]))
			return (envp[i]);
		i++;
	}
	return (NULL);
}

char	*value_is(char *arg, char **envp)
{
	char	*env;
	char	*value;

	env = env_is(arg, envp);
	if (!env)
		return (NULL);
	value = ft_substr(env, ft_strlen(arg) + 1, ft_strlen(env));
	if (!value)
		return (value);
	return (value);
}

char	*get_arg(char *str)
{
	int		i;

	if (!str || !*str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (strchr("\"\'$", str[i]) && i > 0)
			break ;
		i++;
	}
	return (ft_strndup(str, i));
}

t_token	*arg_node(char *str)
{
	t_token	*lst;
	t_token	*node;
	int		i;
	char	*token;

	i = 0;
	while (str[i])
	{
		token = get_arg(&str[i]);
		if (!token)
			return (NULL);
		i += ft_strlen(token);
		node = t_lstnew(token);
		if (!node)
			return (NULL);
		t_lstadd_back(&lst, node);
	}
	return (lst);
}

//int main(int ac, char **av)
//{
//	if (ac != 2)
//		return (1);
//	print_token(arg_node(av[1]));
//}
