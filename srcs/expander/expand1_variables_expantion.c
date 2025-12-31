/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1_variables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:51:16 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/01 03:50:01 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expander.h"

int	append_char_to_str(char **new_argv, char *char_ptr)
{
	char	*new_char;
	char	*joined;

	new_char = ft_strndup(char_ptr, 1);
	if (!new_char)
		return (FAILUER);
	joined = ft_strjoin(*new_argv, new_char);
	if (!joined)
		return (free(new_char), FAILUER);
	free(*new_argv);
	free(new_char);
	*new_argv = joined;
	return (SUCCESS);
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

t_state	manage_quote_expander(char **cur_argv, char **new_argv)
{
	if (**cur_argv == '\'')
	{
		if (append_char_to_str(new_argv, (*cur_argv)) == FAILUER)
			return (FAILUER);
		(*cur_argv)++;
		return (STATE_SQUOTE);
	}
	else if (**cur_argv == '"')
	{
		if (append_char_to_str(new_argv, (*cur_argv)) == FAILUER)
			return (FAILUER);
		(*cur_argv)++;
		return (STATE_DQUOTE);
	}
	return (STATE_GENERAL);
}

int 	manage_state_squote(t_token **cur_list, char **new_argv, t_state *state)
{
	if (*((*cur_list)->token) == '\'')
	{
		*state = STATE_GENERAL;
		if (append_char_to_str(new_argv, (*cur_list)->token) == FAILUER)
			return (FAILUER);
		((*cur_list)->token)++;
		return (SUCCESS);
	}
	if (append_char_to_str(new_argv, (*cur_list)->token) == FAILUER)
			return (FAILUER);
	((*cur_list)->token)++;
	return (SUCCESS);
}

int	manage_state_dquote(char **new_argv, t_token **cur_list, t_state *state,
		t_token *envp)
{
	if (*((*cur_list)->token) == '"')
	{
		*state = STATE_GENERAL;
		if (append_char_to_str(new_argv, (*cur_list)->token) == FAILUER)
			return (FAILUER);
		((*cur_list)->token)++;
		return (SUCCESS);
	}
	else if (*((*cur_list)->token) == '$')
	{
		((*cur_list)->token)++;
		if (hundle_expand_var(new_argv, &((*cur_list)->token), envp) == FAILUER)
			return (FAILUER);
	}
	else
	{
		if (append_char_to_str(new_argv, (*cur_list)->token) == FAILUER)
			return (FAILUER);
		((*cur_list)->token)++;
	}
	return (SUCCESS);
}

int	manage_state_general_expander(char **new_argv, t_token **cur_list,
		t_state *state, t_token *envp)
{
	*state = manage_quote_expander(&(*cur_list)->token, new_argv);
	if (*state != STATE_GENERAL)
		return (SUCCESS);
	if (*((*cur_list)->token) == '$')
	{
		((*cur_list)->token)++;
		if (hundle_expand_var(new_argv, &((*cur_list)->token), envp) == FAILUER)
			return (FAILUER);
	}
	else
	{
		if (append_char_to_str(new_argv, (*cur_list)->token) == FAILUER)
			return (FAILUER);
		((*cur_list)->token)++;
	}
	return (SUCCESS);
}

int	manage_state_transition_variable(t_token **cur_list, t_token *envp)
{
	char	*new_argv;
	char	*old;
	t_state	state;

	if (!ft_strchr((*cur_list)->token, '$'))
		return (SUCCESS);
	old = (*cur_list)->token;
	state = STATE_GENERAL;
	new_argv = ft_strdup("");
	if (!new_argv)
		return (FAILUER);
	while (*(*cur_list)->token)
	{
		if (state == STATE_GENERAL)
		{
			if (manage_state_general_expander(&new_argv, cur_list, &state,
					envp) == FAILUER)
				return (FAILUER);
		}
		else if (state == STATE_DQUOTE)
		{
			if (manage_state_dquote(&new_argv, cur_list, &state,
					envp) == FAILUER)
				return (FAILUER);
		}
		else if (state == STATE_SQUOTE)
		{
			if (manage_state_squote(cur_list, &new_argv, &state) == FAILUER)
				return (FAILUER);
		}
	}
	free(old);
	(*cur_list)->token = new_argv;
	return (SUCCESS);
}

int	expander(t_token **token_list, t_token *envp)
{
	t_token	*tmp;

	if (!token_list)
		return (FAILUER);
	tmp = *token_list;
	while (tmp)
	{
		if (manage_state_transition_variable(&tmp, envp) == FAILUER)
			return (FAILUER);
		
		tmp = tmp->next;
	}
	return (SUCCESS);
}

