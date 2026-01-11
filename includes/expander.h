/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:46:14 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/11 12:39:02 by kesaitou         ###   ########.fr       */
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
}	t_list_type;

bool						is_delimiter_variables(int c);
int							count_varibles(char *av);
t_token						*search_variable(char *key, t_token *envp);
int							expander(t_token **token_list, t_token *envp, t_list_type type);
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
int							match_char(t_token *sub_token, char *file);
int							expand_token(t_token **token_list, t_token *envp);

/*expand1_variable_expantion*/
bool						is_delimiter_variables(int c);
int							count_varibles(char *av);
t_token						*search_variable(char *key, t_token *envp);
char						*value_dup(char *env);
bool						is_dollar(t_token_type type);

/*expand2_path_name_expantion*/
int							insert_token(t_token *src,
								t_token *(*f)(t_token *), t_token *input);
t_token						*wild_card(t_token *sub);
int							strchr_len(char *str, int c);

/*expand_utils*/
bool						is_ifs(char *ifs, int c);
int							ft_strchr_set(char *str, char *set);
char						*setup_ifs(t_token *envp);

void						print_token2(t_token *node);

#endif