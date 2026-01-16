/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer4_subtoken.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 06:22:25 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/16 13:32:49 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

// int	commit_clist(t_token **token, t_char_list *c_list, t_token_type type)
// {
// 	char	*str;

// 	str = NULL;
// 	if (!c_list)
// 		return (SUCCESS);
// 	str = list_to_string(&c_list);
// 	if (!str)
// 		return (FAILUER);
// 	if (str[0] == '\0')
// 		return (free(str), SUCCESS);
// 	add_token(token, str, type);
// 	return (SUCCESS);
// }

// int	commit_word_token(t_token *token_list, t_lexer_builder **c_list,
// 		t_state_tab *state)
// {
// 	t_token	*new;
	
// 	new = NULL;
// 	if (commit_clist(new, c_list, what_type(state->s_sub)) == FAILUER)
// 		return (FAILUER);
// 	state->s_sub = state->s_main;
// 	if (commit_clist(token_list, c_list, TOKEN_WORD) == FAILUER)
// 		return (FAILUER);
// 	token_list->sub_token = new;
// 	return (SUCCESS);
// }



