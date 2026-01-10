/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2_utils3_skip.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 17:33:13 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/10 20:47:04 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

 char	*skip_ifs_whitespace( char *cur,  char *ifs)
{
	while (*cur && is_delimiter_ifs(ifs, *cur) && is_ifs_whitespace(*cur))
		cur++;
	return (cur);
}

 char	*scan_until_delimiter( char *cur,  char *ifs)
{
	while (*cur && !is_delimiter_ifs(ifs, *cur))
		cur++;
	return (cur);
}

 char	*skip_whitespace_delimiters( char *cur,  char *ifs)
{
	while (*cur && is_delimiter_ifs(ifs, *cur) && is_ifs_whitespace(*cur))
		cur++;
	return (cur);
}

char	*consume_whitespace(char *cur, char *ifs, int *need_trailing_empty)
{
	int	consumed_nonws;

	consumed_nonws = 0;
	cur = skip_whitespace_delimiters(cur, ifs);
	if (*cur && is_delimiter_ifs(ifs, *cur) && !is_ifs_whitespace(*cur))
	{
		consumed_nonws = 1;
		cur++;
		cur = skip_whitespace_delimiters(cur, ifs); 
	}
	if (consumed_nonws && *cur == '\0')
		*need_trailing_empty = 1;
	else
		*need_trailing_empty = 0;
	return (cur);
}


 char	*consume_one_nonwhitespace_delimiter(char *cur,
     char *ifs, int *need_trailing_empty)
{
	if (*cur)
		cur++;
	cur = skip_whitespace_delimiters(cur, ifs);
	if (*cur == '\0')
		*need_trailing_empty = 1;
	else
		*need_trailing_empty = 0;
	return (cur);
}

void	skip_set(char **str, char *set)
{
	while (**str && ft_strchr(set, **str))
		(*str)++;
}
