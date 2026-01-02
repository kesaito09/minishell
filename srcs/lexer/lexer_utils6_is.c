/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils6_is.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:23:53 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/02 14:18:42 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

bool	is_operator(char *str)
{
	if (*str == '|' || *str == '<' || *str == '>' || *str == '(' || *str == ')')
		return (true);
	if (!ft_strncmp(str, "&&", 2))
		return (true);
	return (false);
}

bool	is_delimiter(int c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

bool	can_be_splitted(char *str)
{
	if (is_delimiter(*str))
		return (true);
	if (is_operator(str))
		return (true);
	if (!ft_strncmp(str, "&&", 2))
		return (true);
	return (false);
}
