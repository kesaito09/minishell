/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 01:23:57 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/21 16:07:37 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_cmd.h"
#include "../../includes/execution.h"

static int	env_oldpwd(t_shared_info *info);
static int	env_pwd(t_shared_info *info);

int	cd(t_token *node, t_shared_info *info)
{
	char	*cd_;

	if (node && !ft_strcmp(node->token, "-"))
	{
		cd_ = return_value("OLDPWD", info->envp);
		if (!*cd_)
			return (ft_putendl_fd("minishell: cd: HOME not set", 2),
				free(cd_), FAILUER);
	}
	else if (node)
		cd_ = ft_strdup(node->token);
	else
	{
		cd_ = return_value("HOME", info->envp);
		if (!*cd_)
			return (ft_putendl_fd("minishell: cd: HOME not set", 2),
				free(cd_), FAILUER);
	}
	if (!cd_)
		return (FAILUER);
	if (env_oldpwd(info) == FAILUER
		|| chdir(cd_) == FAILUER
		|| env_pwd(info) == FAILUER)
		return (free(cd_), FAILUER);
	return (free(cd_), SUCCESS);
}

static int	env_oldpwd(t_shared_info *info)
{
	t_token	*node;
	char	*pwd;
	char	*new_env;

	pwd = return_value("PWD", info->envp);
	if (!pwd)
		return (FAILUER);
	new_env = ft_strjoin("OLDPWD=", pwd);
	free(pwd);
	if (!new_env)
		return (FAILUER);
	node = t_lstnew(new_env, free);
	if (!node)
		return (FAILUER);
	return (silent_export(node, info, BOTTOM));
}

static int	env_pwd(t_shared_info *info)
{
	t_token	*node;
	char	*pwd;
	char	*new_env;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (FAILUER);
	new_env = ft_strjoin("PWD=", pwd);
	free(pwd);
	if (!new_env)
		return (FAILUER);
	node = t_lstnew(new_env, free);
	if (!node)
		return (FAILUER);
	return (silent_export(node, info, BOTTOM));
}

//int main(void)
//{
//	char	*pwd1;
//	char	**cmd;

//	pwd1 = "pwd";
//	cmd = (char **)malloc(sizeof(char *) * 2);
//	cmd[0] = "cd";
//	cmd[1] = "../";
//	pwd(&pwd1);
//	cd(cmd);
//	pwd(&pwd1);
//	free(cmd);
//}