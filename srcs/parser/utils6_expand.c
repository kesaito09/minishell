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

int	count_env(char *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token[i])
	{
		if (token[i] == '$')
		{
			i++;
			if (ft_strchr("$ \t\n", token[i]))
				return (-1);
			count++;
		}
		i++;
	}
	return (count);
}

char	*extract_arg(char **token)
{
	char	arg;

	while (*token)
	{
		
	}
}

//int main(int ac, char **av)
//{
//	if (ac != 2)
//		return (1);
//	ft_putnbr_fd(count_env(av[1]), 2);
//}
