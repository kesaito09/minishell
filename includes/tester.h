/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 19:21:32 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/09 19:23:12 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_H
# define TESTER_H

# define SUCCESS 1
# define FAILUER -1

#include "minishell.h"
# include <stdlib.h>

typedef struct s_pipe	t_pipe;
typedef struct s_pipe	t_pipe;

void	print_token(t_token *lst);
void	print_flist(t_flist *flist);
void	print_split(char **cmd);
void	print_tree(t_tree *branch);
void	print_tree_rec(t_tree *branch);

#endif