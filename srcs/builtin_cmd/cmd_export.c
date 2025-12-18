/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 06:21:49 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/16 20:44:41 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.h"
#include "../../includes/execution.h"

static int	export_replace(const char *arg, char **envp)
{
	int	len;
	int	j;

	len = (ft_strchr(arg, '=') - arg);
	j = 0;
	while (ft_strncmp(arg, envp[j], len))
		j++;
	free(envp[j]);
	envp[j] = ft_strdup(arg);
	return (SUCCESS);
}

static int export_module(char **cmd, t_pipe *info)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = (char **)ft_calloc(sizeof(char *), count_arr_elem(info->envp) + 2);
	if (!new_env)
		return (FAILUER);
	while (info->envp[i])
	{
		new_env[i] = ft_strdup(info->envp[i]);
		if (!new_env[i])
			return (free_split(new_env), FAILUER);
		i++;
	}
	new_env[i] = ft_strdup(cmd[1]);
	if (!new_env[i])
		return (free_split(new_env), FAILUER);
	free_split(info->envp);
	info->envp = new_env;
	return (SUCCESS);
}

int	export(char **cmd, t_pipe *info)
{
	char	*tmp;

	tmp = ft_strchr(cmd[1], '=');
	if (!tmp || tmp == cmd[1])
		return (FAILUER);
	if (find_arg(cmd[1], info->envp))
		return (export_replace(cmd[1], info->envp));
	if (export_module(cmd, info) == FAILUER)
		return (FAILUER);
	return (SUCCESS);
}

static int	unset_module(char **cmd, t_pipe *info)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = (char **)ft_calloc(sizeof(char *), count_arr_elem(info->envp));
	if (!new_env)
		return (FAILUER);
	i = 0;
	j = 0;
	while(info->envp[j])
	{
		if (!ft_argcmp(cmd[1], info->envp[j]))
			j++;
		if (!info->envp[j])
			break ;
		new_env[i] = ft_strdup(info->envp[j]);
		if (!new_env[i])
			return (free_split(new_env), FAILUER);
		i++;
		j++;
	}
	free_split(info->envp);
	info->envp = new_env;
	return (SUCCESS);
}

int	unset(char **cmd, t_pipe *info)
{
	if (ft_strchr(cmd[1], '='))
		return ((void)ft_printf("unset: %s: invalid parameter name\n"), FAILUER);
	if (!find_arg(cmd[1], info->envp))
		return (FAILUER);
	if (unset_module(cmd, info) == FAILUER)
		return (FAILUER);
	return (SUCCESS);
}

//int main(int ac, char **av)
//{
//	char	*str;

//	str = "b2b";
//	ft_putnbr_fd(find_arg(str, av), 1);
//	(void)ac;
//}