/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 23:55:44 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/05 17:14:05 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define SUCCESS 1
# define FAILUER -1
# define FIRST 2
# define LAST argc - 2

typedef struct s_pipe		t_pipe;
typedef struct s_pid	t_pidlist;
typedef struct s_tree		t_tree;

/*exec1_path*/
t_pipe				correct_info(int argc, char **argv, char **envp);
void				free_path(char **path);

/*exec2_cmd*/
void				manage_cmd(t_tree *branch, t_pipe *info, pid_t pid);
void				manage_my_cmd(t_tree *branch, t_pipe *info, pid_t pid);

/*exec3_pipe*/
void				manage_pipe(t_tree *branch, t_pipe *info, pid_t pid);

/*exec4_redirect.c*/
int					manage_redirect(t_pipe *info, t_tree *branch);

/*exec5_operate.c*/
void				tree_operator(t_tree *branch, t_pipe *info, pid_t pid);

/*exec_utils1_pid*/
void				pid_add_back(t_pidlist **plist, pid_t pid);
t_pidlist			*pid_new(pid_t pid);
void				free_pid(t_pidlist *plist);
void				waitpid_plist(t_pidlist *plist);

/*exec_utils2_error*/
void				error_exit(char **path, char *str, int errno);

/*exec_utils3_pipe*/
int					pipe_update(int	fd_in[2], int fd_out[2]);
int					pipe_terminate(int	fd_in[2], int fd_out[2]);
void				close_fd_in_out(int *fd_in, int *fd_out);
int					dup2_stdin_out(int fd_in, int fd_out);
int					reset_stdin_out(t_pipe *info);


#endif