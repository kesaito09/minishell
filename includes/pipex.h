/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 23:55:44 by natakaha          #+#    #+#             */
/*   Updated: 2025/11/29 18:28:43 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"
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

typedef enum e_token_type
{
	TOKEN_WORD = 0,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_EOF

}					t_token_type;

typedef struct s_tree
{
	char			*op;
	struct s_tree	*left;
	struct s_tree	*right;
	char			**argv;
	t_token_type	mode;

}					t_tree;

typedef struct s_pipe
{
	int				argc;
	char			**envp;
	char			**argv;
	char			**path;
	int				oldfd[2];
	int				newfd[2];
}					t_pipe;

/*parse*/
t_pipe				correct_info(int argc, char **argv, char **envp);
void				free_path(char **path);

/*util_comand*/
void				error_exit(char **path, char *str, int errno);
char				*get_lines(int fd);
void				dup2_or_exit(t_pipe info, int fd1, int fd2);
void				wait_exit(pid_t pid[], t_pipe info);

#endif