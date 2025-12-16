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

# define SUCCESS 1
# define FAILUER -1
# define FIRST 2
# define LAST argc - 2

typedef enum e_tree_type
{
	PIPE = 0,
	CONJUNCTION,
	DISJUNCTION,
	COMMAND,
	MY_COMMAND,
}					t_tree_type;

typedef enum e_file_type
{
	NONE,
	OUTFILE,
	APPEND,
	INFILE,
	HEARDOC,
}			t_file_type;

typedef struct 			s_flist
{
	t_file_type			f_type;
	char				*file;
	struct s_flist	*next;
}			t_flist;

typedef struct s_tree
{
	struct s_tree	*parent;
	struct s_tree	*left;
	struct s_tree	*right;
	char			**argv;
	char			**assigns;
	t_flist			*flist;
	t_tree_type			b_type;
}					t_tree;

typedef struct s_pidlist
{
	int				pid;
	struct s_pidlist	*next;
}					t_pidlist;

typedef struct s_pipe
{
	int				argc;
	char			**envp;
	char			**path;
	bool			pipe;
	int				fd[2];
	t_pidlist		*plist;
	int				fd_stdin;
	int				fd_stdout;
}					t_pipe;

/*exec1_path*/
t_pipe				correct_info(char **envp);
void				free_path(char **path);

/*exec2_cmd*/
int					manage_cmd(t_tree *branch, t_pipe *info, int fd_in, int fd_out);
int					manage_my_cmd(t_tree *branch, t_pipe *info, int fd_in, int fd_out);

/*exec3_pipe*/
int					manage_pipe(t_tree *branch, t_pipe *info, int fd_in, int fd_out);

/*exec4_redirect.c*/
int					manage_redirect(t_tree *branch);

/*exec5_operate.c*/
int					tree_operator(t_tree *branch, t_pipe *info, int fd_in, int fd_out);

/*exec_utils1_pid*/
void				pid_add_back(t_pidlist **plist, pid_t pid);
t_pidlist			*pid_new(pid_t pid);
void				free_pid(t_pidlist *plist);
void				close_unused_pipe(int fd_in, int fd_out, int pipes[2]);
void				waitpid_plist(t_pidlist **plist);

/*exec_utils2_error*/
void				error_exit(char *str, int errno);
void				command_error_check(char *cmd, char *path);
int					redirect_in_check(char *path);
int					redirect_out_check(char *path);

/*exec_utils3_pipe*/
int					pipe_update(int	fd_in[2], int fd_out[2]);
void				close_fd_in_out(int *fd_in, int *fd_out);
int					dup2_stdin_out(int fd_in, int fd_out);
int					reset_stdin_out(t_pipe *info);


#endif