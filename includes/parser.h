/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:44:28 by natakaha          #+#    #+#             */
/*   Updated: 2026/05/05 08:07:01 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
# include <dirent.h>
# include <stdbool.h>

/*struct detail in execution.h*/

extern int						g_signal_code;

typedef struct dirent			t_dirent;
typedef struct s_tree			t_tree;
typedef struct s_flist			t_flist;
typedef enum e_tree_type		t_tree_type;
typedef enum e_state			t_state;
typedef enum e_file_type		t_file_type;
typedef enum e_token_type		t_token_type;
typedef struct s_token			t_token;
typedef struct s_shared_info	t_shared_info;

typedef enum e_op_level
{
	OP_LOGICAL,
	OP_PIPELINE,
	OP_COMMAND,
}								t_op_level;

/* parse1_cmd */
t_tree							*parse_command(t_token **cur,
									t_shared_info *info);

/* parse2_left_join */
t_tree							*parse_left_join(t_token **cur,
									t_shared_info *info, t_op_level level);

/* parse3_parser */
t_tree							*parser(t_shared_info *info);

/* utils1_tree */
t_tree							*tree_new(t_tree_type btype);
void							free_tree_rec(t_tree **branch);

/* utils2_parse */
int								count_element(char **s);
void							free_split(char **cmd);
void							free_and_skip_one(t_token **cur);

/* utils3_is */
bool							is_builtin(char *token);
bool							is_redirect(t_token *cur);
bool							is_connection(t_token *cur);
bool							is_command(t_token *cur);
t_tree_type						cmd_type(t_token *cur);

/* utils4_arglist */
char							**token_argv(t_token *node);
t_token							*argv_token(char **argv);
char							**token_cmd(t_token *node, t_shared_info *info);
t_token							*argv_token(char **argv);

#endif
