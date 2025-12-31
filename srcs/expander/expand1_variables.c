/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:51:16 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/31 06:07:09 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expander.h"

int	hundle_expand_var(char **new_argv, char **cur_argv, t_token *envp)
{
	char	*var;
	char	*tmp;
	char	*joined;
	t_token	*val_ptr;

	tmp = ft_strndup(*cur_argv, count_varibles(*cur_argv));
	if (!tmp)
		return (FAILUER);
	val_ptr = search_variable(tmp, envp);
	if (!val_ptr)
		var = ft_strdup("");
	else
		var = value_dup(val_ptr->token);
	if (!var)
		return (free(tmp), FAILUER);
	joined = ft_strjoin(*new_argv, var);
	if (!joined)
		return (free(tmp), FAILUER);
	free(*new_argv);
	*new_argv = joined;
	(*cur_argv) += count_varibles(*cur_argv);
	return (free(tmp), SUCCESS);
}

t_state	manage_quote_expander(char **cur_argv)
{
	if (**cur_argv == '\'')
	{
		(*cur_argv)++;
		return (STATE_SQUOTE);
	}
	else if (**cur_argv == '"')
	{
		(*cur_argv)++;
		return (STATE_DQUOTE);
	}
	return (STATE_GENERAL);
}

void	manage_state_squote(t_token **cur_list, t_state *state)
{
	if (*((*cur_list) ->token) == '\'')
	{
		*state = STATE_GENERAL;
		((*cur_list) ->token)++;
		return ;
	}
	((*cur_list) ->token)++;
	return ;
}

int	manage_state_dquote(char **new_argv, t_token **cur_list, t_state *state,
		t_token *envp)
{
	if (*((*cur_list) ->token) == '"')
	{
		*state = STATE_GENERAL;
		((*cur_list) ->token)++;
		return (SUCCESS);
	}
	if (*((*cur_list) ->token) == '$')
	{
		((*cur_list) ->token)++;
		if (hundle_expand_var(new_argv, &((*cur_list) ->token), envp) == FAILUER)
			return (FAILUER);
		(*cur_list) ->expanded = true;
	}
	else
		((*cur_list) ->token)++;
	return (SUCCESS);
}

int	manage_state_general_expander(char **new_argv, t_token **cur_list,
		t_state *state, t_token *envp)
{
	*state = manage_quote_expander(&(*cur_list) ->token);
	if (*state != STATE_GENERAL)
		return (SUCCESS);
	if (*((*cur_list) ->token))
	{
		((*cur_list) ->token)++;
		if (hundle_expand_var(new_argv, &((*cur_list) ->token), envp) == FAILUER)
			return (FAILUER);
	}
	else
		((*cur_list) ->token)++;
	return (SUCCESS);
}

int	manage_state_transition_expander(t_token **cur_list, t_token *envp)
{
	char	*new;
	t_state	state;

	if (!ft_strchr((*cur_list)->token, '$'))
		return (SUCCESS);
	state = STATE_GENERAL;
	new = ft_strdup("");
	if (!new)
		return (FAILUER);
	while (*(*cur_list)->token)
	{
		if (state == STATE_GENERAL)
		{
			if (manage_state_general_expander(&new, cur_list, &state,
					envp) == FAILUER)
				return (FAILUER);
		}
		else if (state == STATE_DQUOTE)
		{
			if (manage_state_dquote(&new, cur_list, &state,
					envp) == FAILUER)
				return (FAILUER);
		}
		else if (state == STATE_SQUOTE)
			manage_state_squote(cur_list, &state);
	}
	free((*cur_list)->token);
	(*cur_list)->token = new;
	return (SUCCESS);
}

int	expand_variables(t_token **token_list, t_token *envp)
{
	t_token	*tmp;

	if (!token_list)
		return (FAILUER);
	tmp = *token_list;
	while (tmp)
	{
		if (manage_state_transition_expander(&tmp, envp) == FAILUER)
			return (FAILUER);
		tmp = tmp->next;
	}
	return (SUCCESS);
}
