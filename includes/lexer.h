/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:55:34 by kesaitou          #+#    #+#             */
/*   Updated: 2025/11/23 07:34:29 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "minishell.h"

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
	TOKEN_EOF,
	// リストのヌル文字みたいな意味

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
	struct s_token		*next;
}						t_token;

/*　　一文字ずつ生成していき最終的に連結してトークンにする　　*/
typedef struct s_char_list
{
	char				c;
	struct s_char_list	*next;
}						t_char_list;

typedef struct s_lexer
{
	t_state				state;
	t_token				*token;
	t_char_list			*c_list;

}						t_lexer;

void					buff_add_buck(t_char_list **char_list,
							t_char_list *new_char_list);
void					append_char(t_char_list **list, char c);
char					*list_to_string(t_char_list **list);
void					add_token(t_token **token_list, char *token,
							t_token_type type);
t_token					*t_lstnew(char *token);
size_t					t_lstsize(t_token *lst);
void					t_lstdelone(t_token *lst, void (*del)(void *));
void					t_lstclear(t_token **lst, void (*del)(void *));
t_token					*t_lstlast(t_token *lst);
void					t_lstadd_back(t_token **lst, t_token *new);

t_char_list				*c_lstlast(t_char_list *lst);
size_t					c_lstsize(t_char_list *lst);
void					c_lstclear(t_char_list **lst, void (*del)(void *));

/*batakaha_test*/
t_state					is_quote(char c);
int						quote_len(char *str);
t_token_type 			is_token_type(char *c);
int 					count_section(char *str);
int						section_len(char *str);
char					**split_section(char *str);
int 					lexer(char *input, t_token **token_list);


# endif