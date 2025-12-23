/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2_expand_ifs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 18:16:52 by kesaitou          #+#    #+#             */
/*   Updated: 2025/12/22 20:20:20 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"



void	hundle_quote_field_splitting(char **cur_argv, t_state *state)
{
	if (**cur_argv == '\'')
	{
		*state = STATE_SQUOTE;
		(*cur_argv)++;
	}
	else if (**cur_argv == '"')
	{
		*state = STATE_DQUOTE;
		(*cur_argv)++;
	}
}

void	manage_state_squote_field_splitting(char **cur_argv, t_state *state)
{
	if (**cur_argv == '\'')
	{
		*state = STATE_GENERAL;
		(*cur_argv)++;
		return ;
	}
	(*cur_argv)++;
	return ;
}

int	manage_state_dquote_field_splitting(char **cur_argv, t_state *state,
		t_token *envp)
{
	if (**cur_argv == '"')
	{
		*state = STATE_GENERAL;
		(*cur_argv)++;
		return (SUCCESS);
	}
	else
		(*cur_argv)++;
	return (SUCCESS);
}

static void	manage_state_general_field_splitting(char **cur_argv,
		t_state *state, t_token *envp)
{
	hundle_quote_field_splitting(cur_argv, state);
	if (state != STATE_GENERAL)
		return ;
	(*cur_argv)++;
	return ;
}

int	manage_state_transition_field_splitting(t_token **cur_list, t_token *envp)
{
	char	*cur_argv;
	t_state	state;

	state = STATE_GENERAL;
	cur_argv = (*cur_list)->token;
	while (*cur_argv)
	{
		if (state == STATE_GENERAL)
		{
			manage_state_general_field_splitting(&cur_argv, &state,
					envp);
		}
		else if (state == STATE_DQUOTE)
		{
			if (manage_state_dquote_field_splitting(&cur_argv, &state,
					envp) == FAILUER)
				return (FAILUER);
		}
		else if (state == STATE_SQUOTE)
			manage_state_squote_field_splitting(cur_argv, &state);
	}
	return (SUCCESS);
}



int	field_spliting(t_token **token_list, t_token *envp)
{
	if (!token_list)
		return (FAILUER);
	if (manage_state_transition_expander_ifs(token_list, envp) == FAILUER)
			return (FAILUER);
	return (SUCCESS);
}

/*
	IFSやること
	シングルクォート、なにもしない
	ダブルクォート、展開しない
	ダブルクォート、　展開する
	通常　、展開する

	VAR=a b c d e f g

	"$VAR"
	'$VAR'
		$VAR

		ls -l "$VAR"/
	tokne_listをつくっていく

	ls -l "$VAR"
	t_lstnewでIFSで区切られた文字列をトークンとして連結する




*/
