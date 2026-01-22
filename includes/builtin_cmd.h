/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:58:04 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/23 00:05:19 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_CMD_H
# define BUILTIN_CMD_H

# define SUCCESS 1
# define FAILUER -1

# include "minishell.h"
# include <stdlib.h>
# include <stdbool.h>

extern int						g_exit_code;

typedef struct s_tree			t_tree;
typedef struct s_shared_info	t_shared_info;
typedef struct s_token			t_token;

enum e_export
{
	TOP,
	BOTTOM
}	;

/* builtin_cmd */
int		cd(t_token *node, t_shared_info *info);
int		echo(t_token *node);
int		env(t_token *node, t_shared_info *info);
void	builtin_exit(t_shared_info *info);
int		export(t_token *cmd, t_shared_info *info);
int		silent_export(t_token*cmd, t_shared_info *info, int loc, int type);
int		pwd(t_shared_info *info);
int		unset(t_token *cmd, t_shared_info *info);

/* cmd_utils_env */
int		is_valid_arg(char *arg);
int		ft_argcmp(const char *arg, const char *env);
int		ft_keycmp(const char *arg, const char *env);
char	*return_value(char *arg, t_token *envp);
void	invalid_message(char *arg);

#endif