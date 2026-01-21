/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:46:14 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/21 18:04:24 by natakaha         ###   ########.fr       */
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

typedef enum e_ifs_state
{
	STRT = 0,
	SPCE,
	IFS,
	WORD,
	NLL,
}	t_ifs_state;

typedef enum e_ifs_operate
{
	INCREMENT = 0,
	LEN_INCREMENT = 1,
	STATE_CHANGE = 2,
	ADD_LST = 3,
	FINISH = 4,
}	t_ifs_operate;

/* expand1_env */
t_token		*get_sub_token(char *input, t_token *envp, t_token_type flag);

/* expand2_wildcard */
int			wildcard_expand(t_token *sub, t_token *node, t_list_type type);

/* expand3_expander */
int			expander(t_token *node, t_shared_info *info, t_list_type l_type);

/* expand4_ifs */
int			ifs_expand(t_token *sub, t_token *node, t_list_type type);
int			ifs_split(char *input, char *ifs, t_token **lst, t_ifs_state state);

/* utils1 */
int			envlen(char *av);
int			strchr_len(char *str, int c);
char		*split_join(char **argv);
char		*expand_join(char *input, t_token *envp, t_token_type type);
char		*token_join(t_token *node);

/* utils2_search_file */
int			search_file(t_token *sub_token, char *file);

/* utils3_ifs */
char		*ifs_join(t_token **sub);
bool		has_type(t_token *sub, t_token_type type);
t_ifs_state	is_ifs(char c, char *ifs);
t_token		*ifs_insert(t_token *node, t_token *envp);

#endif