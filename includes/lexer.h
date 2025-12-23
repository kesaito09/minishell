/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:55:34 by kesaitou          #+#    #+#             */
/*   Updated: 2025/12/20 03:28:57 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
#include <stdbool.h>

typedef enum e_token_type
{
	TOKEN_WORD = 0,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_CONJUNCTIONE,
	TOKEN_DISJUNCTIONE,
	TOKEN_PARENTHESIS_LEFT,
	TOKEN_PARENTHESIS_RIGHT,
}						t_token_type;

typedef enum e_state
{
	STATE_GENERAL = 0,
	STATE_SQUOTE,
	STATE_DQUOTE,
}						t_state;

typedef struct s_token
{
	char				*token;
	t_token_type		type;
	t_token				*arg_list;
	struct s_token		*next;
	
}						t_token;

typedef struct s_char_list
{
	char				c;
	struct s_char_list	*next;
}						t_char_list;

/*lexer_utils1_token*/
void					buff_add_buck(t_char_list **char_list,
							t_char_list *new_char_list);
int						append_char(t_char_list **list, char c);
char					*list_to_string(t_char_list **list);
int						add_token(t_token **token_list, char *token,
							t_token_type type);

/*lexer_utils2_list_helpers*/
size_t					t_lstsize(t_token *lst);
t_token					*t_lstnew(char *token);
void					t_lstdelone(t_token *lst, void (*del)(void *));
void					t_lstclear(t_token **lst, void (*del)(void *));
t_token					*t_lstlast(t_token *lst);
void					t_lstadd_back(t_token **lst, t_token *new);

/*lexer_utils3_charlist*/
t_char_list				*c_lstlast(t_char_list *lst);
size_t					c_lstsize(t_char_list *lst);
void					c_lstclear(t_char_list **lst, void (*del)(void *));

/*lexer_utils4_manage_states*/
int						manage_state_transition(t_token **token_list,
							char **input, t_state *state, t_char_list **c_list);

/*lexer_utils5_manage_operaters*/
int						manage_operater(t_token **token_list, char **input);

/*lexer_utils6_helpers*/
int						is_operator(int c);
int						is_delimiter(int c);

/*lexer*/
t_token				*tokenizer(char *input);
#endif