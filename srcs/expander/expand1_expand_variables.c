/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1_expand_variables.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:51:16 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/22 19:40:46 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

t_token	*search_variable(char *key, t_token *envp)
{
	while (envp)
	{
		if (!ft_strcmp(key, envp->token))
			return (envp);
		envp = envp->next;
	}
	return (NULL);
}

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
		var = ft_strdup(val_ptr-> token);
	if (!var)
		return (free(tmp), FAILUER);
	joined = ft_strjoin(*new_argv, tmp);
	if (!joined)
		return (free(tmp), FAILUER);
	free(*new_argv);
	*new_argv = joined;
	(*cur_argv) += count_varibles(*cur_argv);
	return (free(tmp), SUCCESS);
}

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

int	manage_state_transition_expander(t_token **cur_list, t_token *envp)
{
	char	*cur_argv;
	char	*new_argv;
	t_state	state;

	if (!ft_strchr((*cur_list)->token, '$'))
		return (SUCCESS);
	state = STATE_GENERAL;
	cur_argv = (*cur_list)->token;
	new_argv = ft_strdup("");
	while (*cur_argv)
	{
		if (state == STATE_GENERAL)
		{
			if (manage_state_general_expander(&new_argv, &cur_argv, &state,
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
			manage_state_squote(&cur_argv, &state);
	}
	free((*cur_list)->token);
	(*cur_list)->token = new_argv;
	return (SUCCESS);
}

int	expand_variables(t_token **token_list, t_token *envp)
{
	t_token	*cur_list;

	if (!token_list)
		return (FAILUER);
	if (manage_state_transition_expander(token_list, envp) == FAILUER)
		return (FAILUER);
	return (SUCCESS);
}
