/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 18:37:30 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/08 01:26:47 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_H
# define TESTER_H

# include "minishell.h"

typedef struct s_token	t_token;
typedef struct s_flist	t_flist;

void	print_token(t_token *lst);
void	print_flist(t_flist *flist);
void	print_split(char **cmd);
void	print_tree(t_tree *branch);
void	print_tree_rec(t_tree *branch);

# endif
