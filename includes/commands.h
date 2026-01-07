/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:58:04 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/07 20:04:16 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# define SUCCESS 1
# define FAILUER -1

# include "minishell.h"
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_tree	t_tree;
typedef struct s_pipe	t_pipe;
typedef struct s_token	t_token;

int		echo(t_token *node);
void	pwd(void);
void	cd(t_token *node);
void	env(t_token *node, t_pipe *info);
int		export(t_token *node, t_pipe *info);
int		unset(t_token *node, t_pipe *info);
void	builtin_exit(t_tree *branch, t_pipe *info);

int		ft_argcmp(const char *arg, const char *env);
int		ft_keycmp(const char *arg, const char *env);
int		is_valid_arg(char *arg);


#endif