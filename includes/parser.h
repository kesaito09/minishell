/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:44:28 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/17 13:09:05 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

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
int	    tokenizer(char *input, t_token **token_list);
t_tree	*parser(char *input);



# endif
