/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:55:34 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/18 11:17:27 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# include <stdbool.h>

# define OPERATOR "|<>()"
# define DELIMITER " \t\n"
# define SPLIT "|<>() \t\n"
# define QUOTE "\'\""

typedef enum e_token_type
{
	TOKEN_WORD = 0,
	TOKEN_PIPE = '|',
	TOKEN_REDIRECT_IN = '<',
	TOKEN_REDIRECT_OUT = '>',
	TOKEN_HEREDOC = '<' + 128,
	TOKEN_APPEND = '>' + 128,
	TOKEN_CONJUNCTIONE = '|' + 128,
	TOKEN_DISJUNCTIONE = '&' + 128,
	TOKEN_PARENTHESIS_LEFT = '(',
	TOKEN_PARENTHESIS_RIGHT = ')',
	TOKEN_ENVP = '=',
	TOKEN_SPACE = ' ',
	SUB_TOKEN_GENERAL = 'g',
	SUB_TOKEN_SQUOTE = '\'',
	SUB_TOKEN_DQUOTE = '\"',
	SUB_TOKEN_DOLLAR = '$',
	SUB_TOKEN_DOLLAR_DQUOTE = '"' + 128,
	SUB_TOKEN_DOLLAR_QUESTION = '?',

}						t_token_type;

typedef enum e_state
{
	STATE_GENERAL = 'g',
	STATE_SQUOTE = '\'',
	STATE_DQUOTE = '"',
	STATE_DOLLER = '$',
	STATE_DOLLER_DQUOTE = '"' + 127,
	FAIL
}						t_state;

typedef struct s_token
{
	char				*token;
	t_token_type		type;
	struct s_token		*next;
}						t_token;

/* lexer1_tokenize */
int				word_len(char *input, char *charsplit, char *charignore);
t_token			*tokenizer(char *input);

/* utils1_tlist1 */
size_t			t_lstsize(t_token *lst);
t_token			*t_lstmove(t_token *lst, int n);
t_token			*t_lstnew(char *token, void (*del)(void *));
t_token			*f_lstnew(char *token, t_token_type type);

/* utils1_tlist2 */
void			t_lstdelone(t_token *lst, void (*del)(void *));
void			t_lstclear(t_token **lst, void (*del)(void *));
void			t_lstadd_back(t_token **lst, t_token *new);
void			t_lstadd_front(t_token **lst, t_token *new);
void			t_lstadd_sort(t_token **lst, t_token *new);

/* utils4_judge */
bool			is_delimiter(int c);
t_token_type	what_type(int state);
bool			is_env_delimiter(int c);
int				logical_len(char *input);
int				str_type(char *op);

#endif