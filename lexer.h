/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:55:34 by kesaitou          #+#    #+#             */
/*   Updated: 2025/11/28 13:04:05 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef enum e_token_type
{
	TOKEN_WORD = 0,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
	TOKEN_EOF

}						t_token_type;

typedef enum e_state
{
	STATE_GENERAL = 0,
	STATE_SQUOTE,
	STATE_DQUOTE,
}						t_state;

typedef struct s_token_list
{
	char				*token;
	enum e_token_type	type;
	struct s_token_list	*next;
}						t_token_list;

void					lstadd_front(t_token_list **lst, t_token_list *new);
void					lstadd_back(t_token_list **lst, t_token_list *new);
int						lstsize(t_token_list *lst);
t_token_list			*lstlast(t_token_list *lst);
t_token_list			*lstnew(char *token);
void					lstclear_(t_token_list **lst, void (*del)(void *));
void					lstdelone(t_token_list *lst, void (*del)(void *));
t_token_list			*lstmap(t_token_list *lst, void *(*f)(void *),
							void (*del)(void *));
void					lstiter(t_token_list *lst, void (*f)(void *));