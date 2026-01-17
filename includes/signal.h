/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:37:30 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/17 20:06:39 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# define SUCCESS 1
# define FAILUER -1

# include "minishell.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <bits/sigaction.h>

typedef struct s_shared_info	t_shared_info;

void	setup_signal_prompt(void);
void	setup_signal_exec(void);
void	setup_signal_child(void);
int		detect_ecode(int flag, t_shared_info *info);
void	error_exit(char *str, int errno);

#endif