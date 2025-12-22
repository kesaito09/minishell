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



void	manage_quote_expander(char **cur_argv, t_state *state)
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

void	manage_state_squote(char **cur_argv, t_state *state)
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

int	manage_state_dquote(char **new_argv, char **cur_argv, t_state *state,
		t_token *envp)
{
	if (**cur_argv == '"')
	{
		*state = STATE_GENERAL;
		(*cur_argv)++;
		return (SUCCESS);
	}
	if (**cur_argv == '$')
	{
		(*cur_argv)++;
		if (hundle_expand_var(new_argv, cur_argv, envp) == FAILUER)
			return (FAILUER);
	}
	else
		(*cur_argv)++;
	return (SUCCESS);
}

int	manage_state_general_expander(char **new_argv, char **cur_argv,
		t_state *state, t_token *envp)
{
	manage_quote_expander(cur_argv, state);
	if (state != STATE_GENERAL)
		return (SUCCESS);
	if (**cur_argv == '$')
	{
		(*cur_argv)++;
		if (hundle_expand_var(new_argv, cur_argv, envp) == FAILUER)
			return (FAILUER);
	}
	else
		(*cur_argv)++;
	return (SUCCESS);
}

int	manage_state_transition_expander_ifs(t_token **cur_list, t_token *envp)
{
	char	*cur_argv;
	char	*new_argv;
	t_state	state;

	state = STATE_GENERAL;
	cur_argv = (*cur_list)->token;
	while (*cur_argv)
	{
		if (state == STATE_GENERAL)
		{
			if (manage_state_general_expander(&new_argv, &cur_argv, state,
					envp) == FAILUER)
				return (FAILUER);
		}
		else if (state == STATE_DQUOTE)
		{
			if (manage_state_dquote(&new_argv, &cur_argv, &state,
					envp) == FAILUER)
				return (FAILUER);
		}
		else if (state == STATE_SQUOTE)
			manage_state_squote(cur_argv, &state);
	}
	free((*cur_list)->token);
	(*cur_list)->token = new_argv;
	return (SUCCESS);
}


t_token	*field_spliting(char *cur_argv)
{
	
	
	
	
	
	
	
}

int	*expand_ifs(t_token **argv_list)
{
	t_token	*cur_list;

	if (!argv_list)
		return (FAILUER);
	cur_list = *argv_list;
	while (cur_list)
	{
		if (manage_state_transition_expander(&cur_list) == FAILUER)
			return (FAILUER);
		cur_list = cur_list->next;
	}
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
