/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 06:21:49 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/20 06:28:08 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.h"
#include "../../includes/execution.h"

int	strchr_len(const char *arg, char c)
{
	char *ptr;

	ptr = ft_strchr(arg, c);
	return ((int)(ptr - arg));
}

int	ft_argcmp(const char *arg, const char *env)
{
	int	len;

	if (!arg)
		return (-1);
	len = strchr_len(arg, '=');
	if (len < 0)
		return (FAILUER);
	if (ft_strncmp(arg, env, len))
		return (1);
	if (env[len] != '=')
		return (1);
	return (0);
}

int	cmd_check(t_token *cmd)
{
	t_token *env;

	env = cmd->next;
	if (!env)
		return (FAILUER);
	if (strchr_len(env->token, '=') == 0)
	{
		ft_putstr("minishell$: export: '", 2);
		ft_putstr(env->token, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (FAILUER);
	}
	if (!strchr(env->token, '='))
		return (FAILUER);
	return (SUCCESS);
}

int	export(t_token *cmd, t_pipe *info)
{
	t_token	*env;
	char	*arg;

	if (cmd_check(cmd) == FAILUER)
		return (FAILUER);
	arg = ft_strdup(cmd->next->token);
	if (!arg)
		return (FAILUER);
	env = info->envp;
	while (env)
	{
		if (!ft_argcmp(arg, env->token))
		{
			free(env->token);
			env->token = arg;
			return (SUCCESS);
		}
		env = env->next;
	}
	env = t_lstnew(arg);
	if (!env)
		return (free(arg), FAILUER);
	t_lstadd_back(&(info->envp), env);
	(void)cmd;
}

int	unset(t_token *cmd, t_pipe *info)
{
	t_token	*tmp;
	char	*key;


}

//int main(int ac, char **av)
//{
//	char	*str;

//	str = "b2b";
//	ft_putnbr_fd(find_arg(str, av), 1);
//	(void)ac;
//}
