/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 01:23:57 by natakaha          #+#    #+#             */
/*   Updated: 2026/04/29 21:58:08 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin_cmd.h"
#include "../../includes/execution.h"
#include "../../includes/main.h"

static int	is_valid_path(char *path);
static int	key_not_found(char *key);
static char	*resolve_cd_path(t_token *node, t_shared_info *info, char **key);

int	cd(t_token *node, t_shared_info *info)
{
	char	*path;
	char	*key;

	path = resolve_cd_path(node, info, &key);
	if ((!*path && key && key_not_found(key)) || (!is_valid_path(path))
		|| env_oldpwd(info) == FAILURE || chdir(path) == FAILURE
		|| env_pwd(info) == FAILURE)
		return (free(path), FAILURE);
	return (free(path), SUCCESS);
}

static char	*resolve_cd_path(t_token *node, t_shared_info *info, char **key)
{
	char	*path;

	*key = NULL;
	if (node && !ft_strcmp(node->token, "-"))
		*key = "OLDPWD";
	else if (!node)
		*key = "HOME";
	if (*key)
	{
		path = return_value(*key, info->envp);
		if (!path)
			fatal_exit(info);
		ft_putendl_fd(path, 1);
	}
	else
	{
		path = ft_strdup(node->token);
		if (!path)
			fatal_exit(info);
	}
	return (path);
}

static int	key_not_found(char *key)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(key, 2);
	ft_putendl_fd(" not set", 2);
	return (SUCCESS);
}

static int	is_valid_path(char *path)
{
	if (access(path, F_OK) == -1)
		return (ft_putstr_fd("minishell: cd: ", 2), ft_putstr_fd(path, 2),
			ft_putendl_fd(" No such file or directory", 2), FAILURE);
	if (!is_directory(path))
		return (ft_putstr_fd("minishell: cd: ", 2), ft_putstr_fd(path, 2),
			ft_putendl_fd(" Not a directory", 2), FAILURE);
	if (access(path, X_OK) == -1)
		return (ft_putstr_fd("minishell: cd: ", 2), ft_putstr_fd(path, 2),
			ft_putendl_fd(" Permission denied", 2), FAILURE);
	return (SUCCESS);
}
