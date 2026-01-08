/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:46:14 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/08 11:22:24 by kesaitou         ###   ########.fr       */
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

bool						is_delimiter_variables(int c);
int							count_varibles(char *av);
int							expander(t_token **token_list, t_token *envp);
int							field_spliting(t_token **token_list, t_token *envp);
t_token						*search_variable(char *key, t_token *envp);
int							expander(t_token **token_list, t_token *envp);
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
bool						match_char(char *input, char *d_name);
int							expand_token(t_token **token_list, t_token *envp);

/*expand1_variable_expantion*/
bool						is_delimiter_variables(int c);
int							count_varibles(char *av);
t_token						*search_variable(char *key, t_token *envp);
int							expander(t_token **token_list, t_token *envp);
char						*value_dup(char *env);
bool						is_dollar(t_token_type type);
int							strchr_len(char *str, int c);


/*expand_2_field_splitting*/
int							split_token_list(t_token **token_list,
								t_token *envp, t_token_type type);


/*expand2_path_name_expantion*/
int							pathname_expantion(t_token **token_list);
void						wildcard(t_token *node);
int							strchr_len(char *str, int c);

/*expand_utils*/
bool						is_ifs(char *ifs, int c);
int							ft_strchr_len_set(char *str, char *set);
char						*setup_ifs(t_token *envp);
void						skip_set(char **str, char *set);
int							ft_strchr_len_set(char *str, char *set);
char						*join_sub_token(t_token *sub_token);


#endif