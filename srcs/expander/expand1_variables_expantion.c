/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand1_variables_expantion.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:51:16 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/08 03:53:12 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expander.h"

int	strchr_len(char *str, int c)
{
	char	*ptr;

	ptr = ft_strchr(str, c);
	if (!ptr)
		return (-1);
	return ((int)(ptr - str));
}

char	*expand_var(char *str, t_token *envp)
{
	char	*var;
	char	*tmp;
	t_token	*val_ptr;

	tmp = ft_strndup(str, count_varibles(str));
	if (!tmp)
		return (NULL);
	val_ptr = search_variable(tmp, envp);
	if (!val_ptr)
		var = ft_strdup("");
	else
		var = value_dup(val_ptr->token);
	free(tmp);
	return (var);
}

static char	*sub_token_dup(char *sub_token, t_token *envp, int *len)
{
	char	*sub_token_parts;

	if (*len == -1)
	{
		sub_token_parts = ft_strdup(sub_token);
		*len = strchr_len(sub_token, '\0');
	}
	else if (*len == 0)
	{
		sub_token_parts = expand_var(sub_token + 1, envp);
		*len = count_varibles(sub_token + 1) + 1;
	}
	else
		sub_token_parts = ft_strndup(sub_token, *len);
	if (!sub_token_parts)
		return (NULL);
	return (sub_token_parts);
}

static char	*join_sub_token(t_token *sub_token)
{
	char	*joined;
	char	*new_str;

	new_str = ft_strdup("");
	while (sub_token)
	{
		joined = ft_strjoin(new_str, (sub_token)->token);
		if (!joined)
			return (NULL);
		free(new_str);
		new_str = joined;
		(sub_token) = (sub_token)->next;
	}
	return (new_str);
}

static char	*expand_sub_token(char *sub_token, t_token *envp)
{
	char	*new_str;
	char	*parts;
	char	*joined;
	int		len;

	new_str = ft_strdup("");
	while (*sub_token)
	{
		len = strchr_len(sub_token, '$');
		parts = sub_token_dup(sub_token, envp, &len);
		if (!parts)
			return (NULL);
		joined = ft_strjoin(new_str, parts);
		if (!joined)
			return (free(parts), free(new_str), NULL);
		free(new_str);
		new_str = joined;
		sub_token += len;
	}
	return (new_str);
}

static int	replace_sub_token(t_token **sub_token, t_token *envp)
{
	char	*new_sub_token;
	t_token	*tmp;
	int		flag;

	flag = PASS;
	tmp = *sub_token;
	while (tmp)
	{
		if (!is_dollar(tmp->type))
		{
			tmp = tmp->next;
			continue ;
		}
		flag = SUCCESS;
		new_sub_token = expand_sub_token(tmp->token, envp);
		if (!new_sub_token)
			return (FAILUER);
		free(tmp->token);
		tmp->token = new_sub_token;
		tmp = tmp->next;
	}
	return (flag);
}

int	expand_token(t_token **token_list, t_token *envp)
{
	t_token	*tmp;
	char	*new_token;
	int		flag;

	tmp = *token_list;
	while (tmp)
	{
		flag = replace_sub_token(&(tmp->sub_token), envp);
		if (flag == FAILUER)
			return (FAILUER);
		if (flag == PASS)
		{
			tmp = tmp->next;
			continue ;
		}
		new_token = join_sub_token(tmp->sub_token);
		if (!new_token)
			return (FAILUER);
		free(tmp->token);
		tmp->token = new_token;
		tmp = tmp->next;
	}
	return (SUCCESS);
}

// int	expander(t_token **token_list, t_token *envp)
// {
// 	if (expand_token(token_list, envp) == FAILUER)
// 		return (FAILUER);
// 	return (SUCCESS);
// }

/*

	SUB_TOKEN_GENERAL 11,
	SUB_TOKEN_SQUOTE  12,
	SUB_TOKEN_DQUOTE  13,
	SUB_TOKEN_DOLLAR  14,

 echo a$HOME b
TOK: echo -- TYPE: 0
  SUB: echo -- TYPE: 11
TOK: a$HOME -- TYPE: 0
  SUB: a -- TYPE: 11
  SUB: $HOME -- TYPE: 14
TOK: b -- TYPE: 0
  SUB: b -- TYPE: 11
a/home/dev b
minishell$ echo $HOME$PATH$HOME
TOK: echo -- TYPE: 0
  SUB: echo -- TYPE: 11
TOK: $HOME$PATH$HOME -- TYPE: 0
  SUB: $HOME -- TYPE: 14
  SUB: $PATH -- TYPE: 14
  SUB: $HOME -- TYPE: 14
/home/dev/home/dev/.vscode-server/data/User/globalStorage/github.copilot-chat/debugCommand:/home/dev/.vscode-server/data/User/globalStorage/github.copilot-chat/copilotCli:/home/dev/.vscode-server/cli/servers/Stable-994fd12f8d3a5aa16f17d42c041e5809167e845a/server/bin/remote-cli:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin/home/dev
minishell$ echo "a$HOME b$PATH"
TOK: echo -- TYPE: 0
  SUB: echo -- TYPE: 11
TOK: a$HOME b$PATH -- TYPE: 0
  SUB: a -- TYPE: 13
  SUB: $HOME -- TYPE: 14
  SUB:  b -- TYPE: 13
  SUB: $PATH -- TYPE: 14
a/home/dev b/home/dev/.vscode-server/data/User/globalStorage/github.copilot-chat/debugCommand:/home/dev/.vscode-server/data/User/globalStorage/github.copilot-chat/copilotCli:/home/dev/.vscode-server/cli/servers/Stable-994fd12f8d3a5aa16f17d42c041e5809167e845a/server/bin/remote-cli:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
minishell$ echo '$HOME$PATH'
TOK: echo -- TYPE: 0
  SUB: echo -- TYPE: 11
TOK: $HOME$PATH -- TYPE: 0
  SUB: $HOME$PATH -- TYPE: 12
/home/dev/home/dev/.vscode-server/data/User/globalStorage/github.copilot-chat/debugCommand:/home/dev/.vscode-server/data/User/globalStorage/github.copilot-chat/copilotCli:/home/dev/.vscode-server/cli/servers/Stable-994fd12f8d3a5aa16f17d42c041e5809167e845a/server/bin/remote-cli:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
minishell$ echo aa"$HOME"bb
TOK: echo -- TYPE: 0
  SUB: echo -- TYPE: 11
TOK: aa$HOMEbb -- TYPE: 0
  SUB: aa -- TYPE: 11
  SUB: $HOME -- TYPE: 14
  SUB: bb -- TYPE: 11
aa



*/