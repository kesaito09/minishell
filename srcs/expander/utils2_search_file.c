/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_search_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 01:40:49 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/24 09:27:20 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

static void	next_token(t_token **cur_token, char **cur_token_c);
static int	file_token_cmp(t_token **cur_token,	char **cur_token_c,
				char **cur_file_c, t_token_type type);
static int	skip_star(t_token **cur_token, char **cur_token_c,
				t_token_type type);

int	search_file(t_token *sub_token, char *file)
{
	char	*cur_token_c;
	int		flag;

	cur_token_c = sub_token->token;
	if (!file_token_cmp(&sub_token, &cur_token_c, &file, sub_token->type))
		return (false);
	flag = skip_star(&sub_token, &cur_token_c, sub_token->type);
	while (sub_token || *file)
	{
		file_token_cmp(&sub_token, &cur_token_c, &file, sub_token->type);
		if (!sub_token || !*file)
			break ;
		flag = skip_star(&sub_token, &cur_token_c, sub_token->type);
	}
	if (sub_token)
		flag = skip_star(&sub_token, &cur_token_c, sub_token->type);
	if (!sub_token && flag == true)
		return (true);
	if (!sub_token && !*file)
		return (true);
	return (false);
}

static void	next_token(t_token **cur_token, char **cur_token_c)
{
	if (!*cur_token)
		return ;
	*cur_token = (*cur_token)->next;
	if (*cur_token)
		*cur_token_c = (*cur_token)->token;
	else
		**cur_token_c = '\0';
}

static int	file_token_cmp(t_token **cur_token,
	char **cur_token_c, char **cur_file_c, t_token_type type)
{
	int	n;

	if (!cur_token)
		return (true);
	if (type == SUB_TOKEN_GENERAL)
		n = strchr_len(*cur_token_c, '*');
	if (type != SUB_TOKEN_GENERAL || n < 0)
		n = ft_strlen(*cur_token_c);
	if (n == 0)
		return (true);
	if (ft_strncmp(*cur_token_c, *cur_file_c, n))
	{
		(*cur_file_c)++;
		return (false);
	}
	else
	{
		(*cur_file_c) += n;
		(*cur_token_c) += n;
		if (**cur_token_c == '\0')
			next_token(cur_token, cur_token_c);
		return (true);
	}
}

static int	skip_star(t_token **cur_token,
	char **cur_token_c, t_token_type type)
{
	if (type != SUB_TOKEN_GENERAL || **cur_token_c != '*')
		return (false);
	while (**cur_token_c == '*')
		(*cur_token_c)++;
	if (**cur_token_c == '\0')
		next_token(cur_token, cur_token_c);
	return (true);
}
