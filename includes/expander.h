/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:46:14 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/17 19:52:35 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "minishell.h"
# include <dirent.h>

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

bool						is_delimiter_variables(int c);
int							envlen(char *av);
t_token						*search_variable(char *key, t_token *envp);
int							expander(t_token **token_list, t_shared_info *info, t_list_type type);
int							expand_token(t_token **token_list, t_shared_info *info);
char						*value_dup(char *env);
char						*expand_var(char *str, t_token *envp);
typedef struct dirent		t_dirent;
typedef struct s_tree		t_tree;
typedef struct s_flist		t_flist;
typedef enum e_tree_type	t_tree_type;
typedef enum e_file_type	t_file_type;
typedef struct s_token		t_token;

# define PASS 0

/*utils2*/
int							search_file(t_token *sub_token, char *file);

/*expand1_variable_expantion*/
bool						is_delimiter_variables(int c);
int							envlen(char *av);
t_token						*search_variable(char *key, t_token *envp);
char						*value_dup(char *env);
bool						is_dollar(t_token_type type);

/*expand2_path_name_expantion*/
int							manage_insert_token(t_token *src,
								t_token *(*f)(t_token *), t_token *input);
t_token						*wild_card(t_token *sub);
int							strchr_len(char *str, int c);
int							wildcard_expand(t_token **token_list, t_list_type type);

/*expand_utils*/
bool						is_ifs(char *ifs, int c);
int							ft_strchr_set(char *str, char *set);
char						*setup_ifs(t_token *envp);

void						print_token2(t_token *node);
void						print_token(t_token *token);

#endif