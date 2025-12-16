/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:58:04 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/16 20:42:26 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# define SUCCESS 1
# define FAILUER -1

#include "minishell.h"
# include <stdlib.h>

typedef struct s_pipe	t_pipe;

void	echo(char **cmd);
void	pwd(char **cmd);
void	cd(char **cmd);
void	env(char **cmd, t_pipe *info);
int		export(char **cmd, t_pipe *info);
int		unset(char **cmd, t_pipe *info);

int	count_env(char **envp);
int	ft_argcmp(const char *arg, char *src);
int	find_arg(const char *arg, char **envp);

#endif