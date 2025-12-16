/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:37:30 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/16 09:39:42 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
#define READLINE_H

# define SUCCESS 1
# define FAILUER -1

 #include "minishell.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <bits/sigaction.h>

void setup_signal_prompt(void);
void setup_signal_exec(void);
void setup_signal_child(void);

#endif