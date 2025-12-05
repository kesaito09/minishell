/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:46:18 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/05 15:33:34 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

t_state	is_quote(char c)
{
	if (c == '\'')
		return (STATE_SQUOTE);
	else if (c == '"')
		return (STATE_DQUOTE);
	else if (c == '\\')
		return (STATE_BSLASH);
	return (STATE_GENERAL);
}

int	quote_len(char *str)
{
	t_state	state;
	int		i;

	i = 0;
	state = is_quote(str[i]);
	if (state != STATE_SQUOTE && state != STATE_DQUOTE)
		return (0);
	while (str[i + 1])
	{
		if (is_quote(str[i + 1]) == state)
			return (i);
		if (is_quote(str[i + 1]) == STATE_BSLASH)
			i++;
		i++;
	}
	return (ERROR);
}

//int	main(void)
//{
//	char	*str;

//	str = "\'\\\"abcde\'";
//	printf("%s, %d\n", str, quote_len(str));

//}