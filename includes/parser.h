/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:44:28 by natakaha          #+#    #+#             */
/*   Updated: 2025/11/23 10:47:33 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include <stdbool.h>

/*struct detail in execution.h*/

typedef struct s_tree t_tree;
typedef struct s_flist t_flist;
typedef enum e_tree_type t_tree_type;
typedef enum e_file_type t_file_type;
typedef struct s_token t_token;

/*utils1_make_tree*/
t_tree	*tree_new(char **cmd, t_flist *flist, t_tree_type btype);
void	tree_add_left(t_tree **branch, t_tree *node);
void	tree_add_right(t_tree **branch, t_tree *node);
void 	free_split(char **cmd);
void	free_tree_rec(t_tree *branch);

/*utils2_redirect*/
t_flist	*flist_new(t_file_type ftype, char *fname);
void	flist_add_back(t_flist **lst, t_flist *new);
void	free_flist(t_flist *lst);

/*utils3_parse*/
t_tree_type	cmd_type(t_token *cur);
int			count_arr_elem(char **s);
char		**ultimate_strjoin(char **argv, char *new);

/*utils4_heardoc*/
char	*heardoc(char *eof);

/*utils5_is_*/
bool	is_builtin(char *token);
bool	is_redirect(t_token *cur);
bool	is_connection(t_token *cur);
bool	is_command(t_token *cur);

/*parse_cmd*/
t_tree	*parse_command(t_token **cur);
t_tree	*parse_manage(t_token **cur);


/*parse*/
t_tree	*parser(char *input);
# endif
