/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 23:55:44 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/23 04:40:13 by natakaha         ###   ########.fr       */
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

extern int				g_exit_code;

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
	bool			pipe;
	int				fd[2];
	t_pidlist		*plist;
	t_tree			*branch;
	int				fd_stdin;
	int				fd_stdout;
}					t_shared_info;

/* exec1_operate */
int		exec_manage(t_tree *branch, t_shared_info *info, int fd_in, int fd_out);

/* exec2_logical */
int		exec_sshell(t_tree *branch, t_shared_info *info, int fd_in, int fd_out);
int		exec_cjunc(t_tree *branch, t_shared_info *info, int fd_in, int fd_out);
int		exec_djunc(t_tree *branch, t_shared_info *info, int fd_in, int fd_out);
int		exec_pipe(t_tree *branch, t_shared_info *info, int fd_in, int fd_out);

/* exec3_execve */
int		exec_cmd(t_tree *branch, t_shared_info *info, int fd_in, int fd_out);
int		env_underscore(t_token *node, t_shared_info *info);

/* exec4_builtin */
int		exec_built(t_tree *branch, t_shared_info *info, int fd_in, int fd_out);

/* exec5_env */
int		exec_envp(t_tree *branch, t_shared_info *info, int fd_in, int fd_out);

/* exec6_redirect */
int		manage_redirect(t_token *file_lst);

/* utils1_pid */
int		wait_pidlist(t_pidlist **plist);
void	pid_add_back(t_pidlist **plist, pid_t pid);

/* utils2_redirect_error */
int		is_directory(const char *path);
int		redirect_in_check(char *path);
int		redirect_out_check(char *path);
void	command_error_check(char *cmd, t_token *path_node);

/* utils3_logical */
void	close_unused_pipe(int fd_in, int fd_out, int pipes[2]);
int		dup2_stdin_out(int fd_in, int fd_out);
int		reset_stdin_out(t_shared_info *info);
t_token	*discard_local_env(t_token *envp);


/* utils4_find_path */
t_token	*complete_path(char **envp);

#endif