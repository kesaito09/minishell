/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 23:55:44 by natakaha          #+#    #+#             */
/*   Updated: 2026/04/18 22:14:18 by natakaha         ###   ########.fr       */
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

extern int				g_signal_code;

typedef enum e_tree_type
{
	PIPE = 0,
	CONJUNCTION,
	DISJUNCTION,
	COMMAND,
	BUILTIN,
	SUBSHELL,
	ENVP
}					t_tree_type;

typedef enum 
{
	COMMAND_NOT_FOUND = 2,
	IS_A_DIRECTORY = 3,
	PERMISSION_DENIED = 4
}					t_command_error;

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

typedef struct s_shared_info
{
	t_token			*envp;
	t_token			*input;
	t_token			*heardoc;
	bool			pipe;
	int				fd[2];
	t_pidlist		*plist;
	t_tree			*branch;
	int				fd_stdin;
	int				fd_stdout;
	int				last_ecode;
}					t_shared_info;

/* exec1_operate */
int		exec_manage(t_tree *branch, t_shared_info *info, int fd_in, int fd_out);

/* exec2_logical */
int		exec_sshell(t_tree *branch, t_shared_info *info, int fd_in, int fd_out);
int		exec_cjunc(t_tree *branch, t_shared_info *info, int fd_in, int fd_out);
int		exec_djunc(t_tree *branch, t_shared_info *info, int fd_in, int fd_out);
int		exec_pipe(t_tree *branch, t_shared_info *info, int fd_in, int fd_out);

/* exec3_execve */
int		exec_fork(t_tree *branch, t_shared_info *info, int fd_in, int fd_out);
int		env_underscore(t_token *node, t_shared_info *info);

/* exec4_builtin */
int		exec_built(t_tree *branch, t_shared_info *info, int fd_in, int fd_out);

/* exec5_env */
int		exec_envp(t_tree *branch, t_shared_info *info, int fd_in, int fd_out);

/* exec6_redirect */
int		manage_redirect(t_token *file_lst);

/* utils1_pid */
int			wait_pidlist(t_pidlist **plist);
int			pid_add_back(t_pidlist **plist, pid_t pid);

/* utils2_redirect_error */
bool			is_directory(const char *path);
int				redirect_in_check(char *path);
int				redirect_out_check(char *path);
t_command_error	command_error_check(char *cmd);
int				command_error_message(char *cmd, t_command_error errno);

/* utils3_logical */
void	close_unused_pipe(int fd_in, int fd_out, int pipes[2]);
int		dup2_stdin_out(int fd_in, int fd_out);
int		reset_stdin_out(t_shared_info *info);
t_token	*discard_local_env(t_token *envp);


/* utils4_find_path */
t_token	*complete_path(char *path);
char	*find_path(char **envp);


/* utils5_path_split */
char	**path_split(char const *s, char c);

/* utils6_exec_module.c */
int		manage_file_descriptor(int fd_in, int fd_out ,t_shared_info *info, t_tree *branch);
int		manage_expander(t_tree *branch, t_shared_info *info);
int		manage_exporter(t_tree *branch, t_shared_info *info);
char	**manage_arg_load(t_shared_info *info, t_token *node);

#endif