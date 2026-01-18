/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:46:14 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/18 10:18:10 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"
# include <dirent.h>

# define PASS 0

typedef struct dirent		t_dirent;
typedef struct s_tree		t_tree;
typedef struct s_flist		t_flist;
typedef enum e_tree_type	t_tree_type;
typedef enum e_file_type	t_file_type;
typedef struct s_token		t_token;

typedef enum e_list_type
{
	ARG_LIST = 0,
	FILE_LIST,
	ENV_LIST,
}	t_list_type;

/* expand1_env */
t_token	*get_sub_token(char *input, t_token *envp);

/* expand2_wildcard */
int		wildcard_expand(t_token **token_list, t_list_type type);

/* expand3_expander */
int		expander(t_token **node, t_shared_info *info, t_list_type type);

/* utils1 */
int		envlen(char *av);
int		strchr_len(char *str, int c);
void	deep_token_clear(t_token *node);
char	*split_join(char **argv);
char	*expand_join(char *input, t_token *envp);

/* utils2_search_file */
int		search_file(t_token *sub_token, char *file);

/* utils3_heardoc */
char	*heardoc(char *eof, t_token *envp);

#endif