/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2_section.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 15:27:36 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/05 16:28:06 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_token_type is_token_type(char *c)
{
	if (*c == '|')
		return (TOKEN_PIPE);
	else if (*c == '<')
		return (TOKEN_REDIRECT_IN);
	else if (*c == '>')
		return (TOKEN_REDIRECT_OUT);
	else if (*c == '<' && *(c + 1) == '<')
		return (TOKEN_HEREDOC);
	else if (*c == '>' && *(c + 1) == '>')
		return (TOKEN_APPEND);
	else if (*c == ' ')
		return (SPACE);
	return (TOKEN_WORD);
}

int count_section(char *str)
{
	int	i;
	int	tmp;
	int	count;

	count = 1;
	i = 0;
	while (str[i])
	{
		if (is_token_type(&str[i]) == TOKEN_PIPE)
			count++;
		if (is_quote(str[i]) == STATE_SQUOTE
			|| is_quote(str[i]) == STATE_DQUOTE)
		{
			tmp = quote_len(&str[i]);
			if (tmp < 0)
				return (ERROR);
			i += tmp + 1;
		}
		if (is_quote(str[i] == STATE_BSLASH))
			i++;
		i++;
	}
	return (count);
}

int	section_len(char *str)
{
	int	i;
	int	tmp;

	i = 0;
	while (str[i])
	{
		if (is_token_type(&str[i]) == TOKEN_PIPE)
			return (i);
		if (is_quote(str[i]) == STATE_SQUOTE
			|| is_quote(str[i]) == STATE_DQUOTE)
		{
			tmp = quote_len(&str[i]);
			if (tmp < 0)
				return (ERROR);
			i += tmp + 1;
		}
		if (is_quote(str[i] == STATE_BSLASH))
			i++;
		i++;
	}
	return (i);
}

char	**split_section(char *str)
{
	char	**splitted;
	int		n;
	int		j;
	int		sec;

	sec = count_section(str);
	if (sec <= 0)
		return (NULL);
	splitted = (char **)ft_calloc(sec + 1, sizeof(char *));
	if (!splitted)
		return (NULL);
	splitted[sec] = NULL;
	j = 0;
	n = 0;
	while (j < sec)
	{
		n = section_len(str);
		splitted[j] = ft_strndup(str, n);
		str += n + 1;
		j++;
	}
	return (splitted);
}

/*tester*/

//int main(void)
//{
//	char	*str;
//	char	**splitted;
//	int		j;

//	str = "123456789\"|\"|123456789|a";
//	splitted = split_section(str);
//	j = 0;
//	while (splitted[j])
//	{
//		printf("%s\n", splitted[j]);
//		j++;
//	}
//}