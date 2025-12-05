/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:44:28 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/05 14:24:35 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/*struct detail in pipex.h*/

typedef struct s_tree t_tree;
typedef struct s_flist t_flist;
typedef enum e_type t_type;
typedef enum e_file_type t_file_type;

/*utils1_make_tree*/
t_tree	*tree_new(char **cmd, t_flist *flist, t_type btype);
void	tree_add_left(t_tree **branch, t_tree *node);
void	tree_add_right(t_tree **branch, t_tree *node);

/*utils2_redirect*/
t_flist	*flist_new(t_file_type ftype, char *fname);
void	flist_add_back(t_flist **lst, t_flist *new);
void	free_flist(t_flist *lst);

# endif
