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

static int	replace(const char *arg, char **envp)
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

static int allocate_split(char **new_env, char **cmd, t_pipe *info)
{
	int	i;

	i = 0;
	while (info->envp[i])
	{
		new_env[i] = ft_strdup(info->envp[i]);
		i++;
	}
	new_env[i] = ft_strdup(cmd[1]);
	free_split(info->envp);
	if (!new_env[i])
		return (FAILUER);
	info->envp = new_env;
	return (SUCCESS);
}

int	export(char **cmd, t_pipe *info)
{
	char	*tmp;
	char	**new_env;

	tmp = ft_strchr(cmd[1], '=');
	if (!tmp || tmp == cmd[1])
		return (FAILUER);
	if (find_arg(cmd[1], info->envp))
		return (replace(cmd[1], info->envp));
	new_env = (char **)ft_calloc(sizeof(char *), count_env(info->envp) + 2);
	if (!new_env)
		return (FAILUER);
	if (allocate_split(new_env, cmd, info) == FAILUER)
		return (FAILUER);
	return (SUCCESS);
}

int	unset(char **cmd, t_pipe *info)
{
	char	**new_env;
	int		i;
	int		j;

	if (ft_strchr(cmd[1], '='))
		return ((void)ft_printf("unset: %s: invalid parameter name\n"), FAILUER);
	if (!find_arg(cmd[1], info->envp))
		return (FAILUER);
	new_env = (char **)ft_calloc(sizeof(char *), count_env(info->envp));
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
		new_env[i++] = ft_strdup(info->envp[j++]);
	}
	//free_split(info->envp);
	info->envp = new_env;
	return (SUCCESS);
}

//int main(int ac, char **av)
//{
//	char	*str;

//	str = "b2b";
//	ft_putnbr_fd(find_arg(str, av), 1);
//	(void)ac;
//}