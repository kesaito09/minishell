/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:37:30 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/17 20:06:39 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define SUCCESS 1
# define FAILURE -1

# include "minishell.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <signal.h>

extern int						g_signal_code;
typedef struct s_shared_info	t_shared_info;



/* ascii.c */
void			print_logo(void);
void			print_fire(int i);


/* utils1_env.c */  
int				detect_ecode(int flag, t_shared_info *info);
int				env_exit_code(int i, int flag, t_shared_info *info);
int				env_shlvl(t_shared_info *info);
int				env_underscore(t_token *node, t_shared_info *info);

/* utils2_signal.c */
void			setup_signal_prompt(void);
void			setup_signal_exec(void);
void			setup_signal_child(void);

/* utils3.c */
t_shared_info	collect_info(char **envp);
char			*handle_prompt(t_token *envp);
char			*get_line(int fd);
t_token			*script_split(char *input);
int				env_shlvl(t_shared_info *info);

/* fatal_exit.c */
void			fatal_exit(t_shared_info *info);
void			child_fatal_exit(t_shared_info *info);

#endif