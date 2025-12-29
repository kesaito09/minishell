/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 18:46:14 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/28 19:29:30 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

#include "minishell.h"
# include <dirent.h>

typedef struct dirent t_dirent;
typedef struct s_tree t_tree;
typedef struct s_flist t_flist;
typedef enum e_tree_type t_tree_type;
typedef enum e_file_type t_file_type;
typedef struct s_token t_token;

bool is_delimiter_variables(int c);
int count_varibles(char *av);
int	expand_variables(t_token **token_list, t_token *envp);
int	field_spliting(t_token **token_list, t_token *envp);
t_token	*search_variable(char *key, t_token *envp);
int	expand_variables(t_token **token_list, t_token *envp);
char	*value_dup(char	*env);


#endif