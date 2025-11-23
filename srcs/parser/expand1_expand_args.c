/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1_expand_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:51:16 by natakaha          #+#    #+#             */
/*   Updated: 2025/11/23 18:50:05 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

static int is_delimiter_variables(int c)
{
	return (c != '_' || !ft_isalnum(c));
}

static	int count_varibles(char *av)
{
	int	len;

	len = 0;
	while (*av && is_delimiter_variables(*av))
		len++;
	return (len);
}

int hundle_expand_var(t_token **cur_list, char **cur_argv, t_state state, char *shell_var)
{
	char	*var;
	char	*tmp;
	int		var_name_len;

	(void)shell_var;
	var_name_len = count_varibles(*cur_argv);
	tmp = ft_strndup(*cur_argv, var_name_len);
	if (!tmp)
		return (FAILUER);
	var = getenv(tmp);
	if (!var)
		return (free(tmp), SUCCESS);
	free((*cur_list) ->token); 
	free(tmp);
	tmp = ft_strdup(var);
	if (!tmp)
		return (FAILUER);
	(*cur_list) ->token = tmp;
	(*cur_argv) += var_name_len;
	return (free(tmp), SUCCESS);
}

static void	manage_quote_expander(char **av, t_state *state)
{
	if (**av == '\'')
	{
		*state = STATE_SQUOTE;
		(*av)++;
	}
	else if (**av == '"')
	{
		*state = STATE_DQUOTE;
		(*av)++;
	}
}

int manage_state_dquote(t_token **cur_list, char **cur_argv, t_state *state)
{
	if (**cur_argv == '$')
	{
		(*cur_argv)++;
		if (hundle_expand_var(cur_list, cur_argv, *state, NULL) == FAILUER)
			return (FAILUER);
	}
	else
		(*cur_argv)++;
	return (SUCCESS);
}

int manage_state_general_expander(t_token **cur_list, char **cur_argv, t_state *state)
{
	manage_quote_expander(cur_argv, state);
	if (state != STATE_GENERAL)
		return (SUCCESS);
	if (**cur_argv == '$')
	{
		(*cur_argv)++;
		if (hundle_expand_var(cur_list, cur_argv, *state, NULL) == FAILUER)
			return (FAILUER);
	}
	else
		(*cur_argv)++;
	return (SUCCESS);
}

int  manage_state_transition_expander(t_token **cur_list)
{
	char	*cur_argv;
	t_state state;

	if (!ft_strchr((*cur_list) ->token, '$'))
			return (SUCCESS);
	state = STATE_GENERAL;
	cur_argv = (*cur_list) ->token;
	while (*cur_argv)
	{
		if (state == STATE_GENERAL)
		{
			if (manage_state_general_expander(cur_list, &cur_argv, state) == FAILUER)
				return (FAILUER);
		}
		else if (state == STATE_DQUOTE)
		{

			
		}
		else if (state == STATE_SQUOTE)
			(*cur_argv)++;		
		
	}
	return (SUCCESS);
	
	
	
	
}

int	*expand_variables(t_token **token_list)
{
	t_token *cur_list;

	if (!token_list)
		return (FAILUER);
	cur_list = *token_list;
	while (cur_list)
	{
		if (manage_state_transition_expander(&cur_list) == FAILUER)
			return (FAILUER);
		cur_list = cur_list ->next;
	}
	return (SUCCESS);
	
}

int expander(t_token *token_list, char *ifs)
{
	
	
	
	
	
	
	
	
	
	
}

