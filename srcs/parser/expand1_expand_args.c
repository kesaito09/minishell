/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1_expand_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:51:16 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/22 17:49:58 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

static int	is_delimiter_variables(int c)
{
	if (c == '_' || ft_isalnum(c))
		return (0);
	return (1);
}

static int	count_varibles(char *av)
{
	int	len;

	len = 0;
	while (*av && is_delimiter_variables(*av))
		len++;
	return (len);
}

int search_variable(char *key, t_token *envp)
{
	while (envp)
	{
		if (!ft_strcmp(key, envp ->token))
			return (SUCCESS);
		envp = envp ->next;
	}
	return (FAILUER);
}




int	hundle_expand_var(char **new_argv, char **cur_argv, t_token *envp)
{
	char	*var;
	char	*tmp;
	char	*joined;
	int		var_name_len;

	var_name_len = count_varibles(*cur_argv);
	tmp = ft_strndup(*cur_argv, var_name_len);
	if (!tmp)
		return (FAILUER);
	if (search_variable(tmp, envp) == FAILU
		tmp = ft_strdup("");
	else
		tmp = ft_strdup(var);
	if (!tmp)
		return (FAILUER);
	joined = ft_strjoin(*new_argv, tmp);
	if (!joined)
		return (free(tmp), FAILUER);
	free(*new_argv);
	*new_argv = joined;
	(*cur_argv) += var_name_len;
	return (free(tmp), SUCCESS);
}

static void	manage_quote_expander(char **cur_argv, t_state *state)
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

static void	manage_state_squote(char **cur_argv, t_state *state)
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

int	manage_state_dquote(char **new_argv, char **cur_argv, t_state *state)
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
		if (hundle_expand_var(new_argv, cur_argv, NULL) == FAILUER)
			return (FAILUER);
	}
	else
		(*cur_argv)++;
	return (SUCCESS);
}

int	manage_state_general_expander(char **new_argv, char **cur_argv,
		t_state *state)
{
	manage_quote_expander(cur_argv, state);
	if (state != STATE_GENERAL)
		return (SUCCESS);
	if (**cur_argv == '$')
	{
		(*cur_argv)++;
		if (hundle_expand_var(new_argv, cur_argv, NULL) == FAILUER)
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
			if (manage_state_general_expander(cur_list, &cur_argv,
					state) == FAILUER)
				return (FAILUER);
		}
		else if (state == STATE_DQUOTE)
		{
			if (manage_state_dquote(cur_list, &cur_argv, &state) == FAILUER)
				return (FAILUER);
		}
		else if (state == STATE_SQUOTE)
			manage_state_squote(cur_list, cur_argv);
	}
	free((*cur_list)->token);
	(*cur_list)->token = new_argv;
	return (SUCCESS);
}


int	*expand_variables(t_token **token_list, t_token	*envp)
{
	t_token	*cur_list;

	if (!token_list)
		return (FAILUER);
	cur_list = *token_list;
	while (cur_list)
	{
		if (manage_state_transition_expander(&cur_list) == FAILUER)
			return (FAILUER);
		cur_list = cur_list->next;
	}
	return (SUCCESS);
}
