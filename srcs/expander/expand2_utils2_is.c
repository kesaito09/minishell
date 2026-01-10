/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2_utils2_is.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 17:29:34 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/10 18:33:04 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"


bool	is_ifs_whitespace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (true);
	return (false);
}

bool	is_delimiter_ifs(char *ifs, int c)
{
	if (!ifs)
		return (false);
	if (ft_strchr(ifs, c))
		return (true);
	return (false);
}

bool	is_only_whitespace(char *ifs)
{
	int	i;

	i = 0;
	while (ifs && ifs[i])
	{
		if (!is_ifs_whitespace(ifs[i]))
			return (false);
		i++;
	}
	return (true);
}
