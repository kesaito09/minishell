/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:55:34 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/02 17:52:50 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# include <stdbool.h>

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
	TOKEN_ENVP,
	SUB_TOKEN_GENERAL,
	SUB_TOKEN_SQUOTE,
	SUB_TOKEN_DQUOTE,
	SUB_TOKEN_DOLLAR,

}						t_token_type;

typedef enum e_state
{
	STATE_GENERAL = 'g',
	STATE_SQUOTE = '\'',
	STATE_DQUOTE = '"',
	DOLLAR = '$',
}						t_state;

typedef struct s_token
{
	char				*token;
	t_token_type		type;
	struct s_token		*sub_token;
	struct s_token		*next;
}						t_token;

typedef struct s_char_list
{
	char				c;
	struct s_char_list	*next;
}						t_char_list;

typedef struct s_clist
{
	t_char_list			*token_clist;
	t_char_list			*sub_clist;
}t_clist;


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
void					t_lstadd_front(t_token **lst, t_token *new);

/*lexer_utils3_charlist*/
t_char_list				*c_lstlast(t_char_list *lst);
size_t					c_lstsize(t_char_list *lst);
void					c_lstclear(t_char_list **lst, void (*del)(void *));
int						add_commit_token(t_token **token_list,
							t_char_list **c_lsit, t_token_type type);

/*lexer_utils4_manage_states*/
int						manage_state_transition(t_token **token_list,
							char **input, int *state, t_char_list **c_list);

/*lexer_utils5_manage_operaters*/
int						manage_operater(t_token **token_list, char **input);

/*lexer_utils6_is*/
bool					is_operator(char *str);
bool					is_delimiter(int c);
bool					can_be_splitted(char *str);
bool					is_sub_token(t_token_type type);


/*lexer*/
t_token					*tokenizer(char *input);

/*debug*/
void	print_token_ke(t_token *token_list);

#endif