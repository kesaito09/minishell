/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 23:55:44 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/03 03:00:19 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "minishell.h"
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

typedef enum e_type
{
	PIPE = 0,
	COMMAND,
	MY_COMMAND,
}					t_type;

typedef enum e_file_type
{
	NONE,
	OUTFILE,
	APPEND,
	INFILE,
}			t_file_type;

typedef struct 			s_flist
{
	t_file_type			f_type;
	char				*file;
	struct s_filelist	*next;
}			t_flist;

typedef struct s_tree
{
	struct s_tree	*parent;
	struct s_tree	*left;
	struct s_tree	*right;
	char			**argv;
	t_flist			*flist;
	t_type			b_type;
}					t_tree;

typedef struct s_pid
{
	int				pid;
	struct s_pid	*next;
}					t_pidlist;

typedef struct s_pipe
{
	int				argc;
	char			**envp;
	char			**argv;
	char			**path;
	int				fd_in[2];
	int				fd_out[2];
	t_pidlist		*plist;
	int				fd_stdin;
	int				fd_stdout;
}					t_pipe;

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
void				close_fd_in_out(int *fd_in, int *fd_out);
int					dup2_stdin_out(int fd_in, int fd_out);
int					reset_stdin_out(t_pipe *info);


#endif