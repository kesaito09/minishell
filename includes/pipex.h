/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 23:55:44 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/02 07:17:19 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"
# include "commands.h"
# include "readline.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define SUCCESS 1
# define FAIL -1
# define FIRST 2
# define LAST argc - 2

typedef enum e_type
{
	PIPE = 0,
	COMMAND,
	MY_COMMAND,
}					t_type;

typedef struct s_tree
{
	struct s_tree	*op;
	struct s_tree	*left;
	struct s_tree	*right;
	char			**argv;
	char			*redirect_in;
	char			*append;
	char			*redirect_out;
	t_type			state;
}					t_tree;

typedef struct s_pid
{
	int				pid;
	struct s_pid	*next;
}					t_pid;

typedef struct s_pipe
{
	int				argc;
	char			**envp;
	char			**argv;
	char			**path;
	int				fd_in[2];
	int				fd_out[2];
	t_pid			*plist;
}					t_pipe;

/*parse*/
t_pipe				correct_info(int argc, char **argv, char **envp);
void				free_path(char **path);

/*util_pipe*/
void				pid_add_back(t_pid **plist, pid_t pid);
t_pid				*pid_new(pid_t pid);
void				free_pid(t_pid *plist);

/*util_error*/
void				error_exit(char **path, char *str, int errno);
void				wait_exit(pid_t pid[], t_pipe info);

/*cmd_redirect.c*/
int					manage_redirect(t_pipe *info, t_tree *branch);
int					manage_fd(t_pipe *info);
int					fd_stdout(t_pipe *info);
/*tree_operate.c*/
void				tree_operator(t_tree *branch, t_pipe info, pid_t pid,
						t_pid **plist);

/*tree_cmd.c*/
void				manage_cmd(t_tree *branch, t_pipe info, pid_t pid,
						t_pid **plist);
void				manage_my_cmd(t_tree *branch, t_pipe info, pid_t pid,
						t_pid **plist);

#endif