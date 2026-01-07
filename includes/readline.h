/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:37:30 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/07 18:07:40 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

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

typedef struct s_pipe	t_pipe;

void	setup_signal_prompt(void);
void	setup_signal_exec(void);
void	setup_signal_child(void);

int		detect_ecode(int flag, t_pipe *info);
void	error_exit(char *str, int errno);

#endif