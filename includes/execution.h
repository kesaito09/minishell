/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 23:55:44 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/16 15:59:23 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

extern int				g_signal_code;

typedef enum e_tree_type
{
	PIPE = 0,
	CONJUNCTION,
	DISJUNCTION,
	COMMAND,
	BUILTIN,
	SUBSHELL,
	NONE,
	ENVP
}						t_tree_type;

typedef enum e_command_error
{
	COMMAND_NOT_FOUND = 2,
	IS_A_DIRECTORY = 3,
	PERMISSION_DENIED = 4
}						t_command_error;

typedef struct s_token	t_token;

typedef struct s_tree
{
	struct s_tree		*left;
	struct s_tree		*right;
	t_token				*arg_list;
	t_token				*file_list;
	t_token				*env_list;
	t_token				*heredoc;
	t_tree_type			b_type;
}						t_tree;

typedef struct s_pidlist
{
	int					pid;
	struct s_pidlist	*next;
}						t_pidlist;

typedef struct s_shared_info
{
	t_token				*envp;
	t_token				*input;
	bool				pipe;
	int					fd[2];
	t_pidlist			*plist;
	t_tree				*branch;
	int					fd_stdin;
	int					fd_stdout;
	int					last_ecode;
}						t_shared_info;

/* exec0_dispatch.c */
int						exec_manage(t_tree *branch, t_shared_info *info,
							int fd_in, int fd_out);

/* exec1_logical.c */
int						exec_sshell(t_tree *branch, t_shared_info *info,
							int fd_in, int fd_out);
int						exec_cjunc(t_tree *branch, t_shared_info *info,
							int fd_in, int fd_out);
int						exec_djunc(t_tree *branch, t_shared_info *info,
							int fd_in, int fd_out);
int						exec_pipe(t_tree *branch, t_shared_info *info,
							int fd_in, int fd_out);

/* exec2_execve.c */
int						exec_fork(t_tree *branch, t_shared_info *info,
							int fd_in, int fd_out);
int						env_underscore(t_token *node, t_shared_info *info);

/* exec3_builtin.c */
int						builtin_fork(t_tree *branch, t_shared_info *info,
							int fd_in, int fd_out);

/* fd0_manage.c */
int						manage_redirect(t_tree *branch, t_shared_info *info);

/* fd1_heredoc.c */
int						heredoc_open_dup2(t_token *flist, t_tree *branch,
							t_shared_info *info);

/* utils2_child.c */
int						manage_file_descriptor(int fd_in, int fd_out,
							t_shared_info *info, t_tree *branch);
int						manage_expander(t_tree *branch, t_shared_info *info);
int						manage_exporter(t_tree *branch, t_shared_info *info);
char					**manage_arg_load(t_shared_info *info, t_token *node);

/* utils2_env.c */
t_token					*discard_local_env(t_token *envp);

/* utils2_path_search.c */
t_token					*complete_path(t_token *envp, t_shared_info *info);
char					*find_path(char **envp);

/* utils2_path_split.c */
char					**path_split(char const *s, char c,
							t_shared_info *info);

/* utils3_builtin.c */
int						builtin_file_descriptor(int fd_in, int fd_out,
							t_shared_info *info, t_tree *branch);
int						builtin_expander(t_tree *branch, t_shared_info *info);
int						builtin_exporter(t_tree *branch, t_shared_info *info);
char					**builtin_arg_load(t_shared_info *info, t_token *node);

/* core_heredoc.c */
char					*heredoc(char *eof, t_tree *branch,
							t_shared_info *info);
int						heredoc_write_context(char *delimiter, int fd);

/* core_heredoc_search.c */
int						search_heredoc(t_shared_info *info, t_tree *branch);

/* core_heredoc_utils.c */
void					heredoc_clear(t_token **heredoc);
void					heredoc_unlink_files(t_token *heredoc);
void					heredoc_free_list(t_token **heredoc);
void					heredoc_error_message(void);
void					heredoc_unlink_tree(t_tree *branch);

/* core_fd.c */
void					close_unused_pipe(int fd_in, int fd_out, int pipes[2]);
int						dup2_stdin_out(int fd_in, int fd_out);
int						reset_stdin_out(t_shared_info *info);

/* core_err_check.c */
bool					is_directory(const char *path);
int						redirect_in_check(char *path);
int						redirect_out_check(char *path);
t_command_error			command_error_check(char *cmd, bool cur);
int						command_error_message(char *cmd, t_command_error err);

/* core_err_messages.c — message + last_ecode をセットで設定し FAILURE を返す */
int						err_no_such_file(t_shared_info *info, char *path);
int						err_is_a_directory(t_shared_info *info, char *path);
int						err_permission_denied(t_shared_info *info, char *path);
int						err_command_not_found(t_shared_info *info, char *cmd);
int						err_syntax(t_shared_info *info, char *tok);

/* core_pid.c */
int						wait_pidlist(t_pidlist **plist);
int						pid_fix(int status);
int						pid_add_back(t_pidlist **plist, pid_t pid);

#endif
