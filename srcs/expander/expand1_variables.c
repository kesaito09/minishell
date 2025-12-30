/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:51:16 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/30 12:52:16 by natakaha         ###   ########.fr       */
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
	*state = manage_quote_expander(cur_argv);
	if (*state != STATE_GENERAL)
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

int	manage_state_transition_expander(t_token **cur_list, t_token *envp)
{
	char	*token;
	char	*new;

	if (!ft_strchr((*cur_list)->token, '$'))
		return (SUCCESS);
	token = (*cur_list)->token;
	new = expand_str(token, envp);
	free(token);
	(*cur_list)->token = new;
	return (SUCCESS);
}

char	*expand_str(char *str, t_token *envp)
{
	t_state	state;
	char	*new;

	new = ft_strdup("");
	if (!new)
		return (NULL);
	state = STATE_GENERAL;
	while (*str)
	{
		if (state == STATE_GENERAL)
		{
			if (manage_state_general_expander(&new, &str, &state,
					envp) == FAILUER)
				return (NULL);
		}
		else if (state == STATE_DQUOTE)
		{
			if (manage_state_dquote(&new, &str, &state,
					envp) == FAILUER)
				return (NULL);
		}
		else if (state == STATE_SQUOTE)
			manage_state_squote(&str, &state);
	}
	return (new);
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
