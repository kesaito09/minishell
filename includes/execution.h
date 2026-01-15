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
# include <stdbool.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/stat.h>

typedef enum e_tree_type
{
	PIPE = 0,
	CONJUNCTION,
	DISJUNCTION,
	COMMAND,
	MY_COMMAND,
	SUBSHELL,
	ENVP
}					t_tree_type;

typedef struct s_token	t_token;

typedef struct s_tree
{
	struct s_tree	*left;
	struct s_tree	*right;
	t_token			*arg_list;
	t_token			*file_list;
	t_token			*env_list;
	t_tree_type		b_type;

}					t_tree;

typedef struct s_pidlist
{
	int					pid;
	struct s_pidlist	*next;
}						t_pidlist;

typedef struct s_pipe
{
	t_token			*envp;
	bool			pipe;
	int				fd[2];
	t_pidlist		*plist;
	int				ecode;
	int				fd_stdin;
	int				fd_stdout;
}					t_pipe;

/*exec1_path*/
t_pipe				collect_info(char **envp);
void				free_path(char **path);

/*exec2_cmd*/
int					manage_cmd(t_tree *branch, t_pipe *info, int fd_in, int fd_out);
int					manage_my_cmd(t_tree *branch, t_pipe *info, int fd_in, int fd_out);

/*exec3_pipe*/
int					manage_pipe(t_tree *branch, t_pipe *info, int fd_in, int fd_out);
int					manage_subshell(t_tree *branch, t_pipe *info, int fd_in, int fd_out);
int					manage_conjunction(t_tree *branch, t_pipe *info, int fd_in, int fd_out);
int					manage_disjunction(t_tree *branch, t_pipe *info, int fd_in, int fd_out);
int					manage_envp(t_tree *branch, t_pipe *info, int fd_in, int fd_out);

/*exec4_redirect.c*/
int					manage_redirect(t_tree *branch);

/*exec5_operate.c*/
int					tree_operator(t_tree *branch,
						t_pipe *info, int fd_in, int fd_out);

/*exec_utils1_pid*/
void				pid_add_back(t_pidlist **plist, pid_t pid);
t_pidlist			*pid_new(pid_t pid);
void				free_pid(t_pidlist *plist);
void				close_unused_pipe(int fd_in, int fd_out, int pipes[2]);
int					waitpid_plist(t_pidlist **plist);

/*exec_utils2_error*/
void				command_error_check(char *cmd, char *path);
int					redirect_in_check(char *path);
int					redirect_out_check(char *path);

/*exec_utils3_pipe*/
int					pipe_update(int fd_in[2], int fd_out[2]);
void				close_fd_in_out(int *fd_in, int *fd_out);
int					dup2_stdin_out(int fd_in, int fd_out);
int					reset_stdin_out(t_pipe *info);

/*utils4_env*/
bool				has_cmd(t_token *args);
int					local_env(t_token *env, t_pipe *info);

void				print_tokens(t_token *node);

#endif