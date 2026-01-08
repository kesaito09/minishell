/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_match_char.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 01:40:49 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/08 01:43:00 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

static void	skip_star(char **input)
{
	while (**input && **input == '*')
		(*input)++;
}

static int	increment(char **input, char **match)
{
	if (**input == '*' || **input != **match)
		return (SUCCESS);
	if (!**input || !**match)
		return (FAILUER);
	if (**input != **match)
		return (FAILUER);
	(*input)++;
	(*match)++;
	return (SUCCESS);
}

static int	reset(char **input, char **d_name, char *start, char **match)
{
	if (**input == '*' || **input == **match)
		return (SUCCESS);
	*input = start;
	if (!**match)
		return (FAILUER);
	*d_name = (*match)++;
	return (SUCCESS);
}

static int	star_skip(char **start, char **match, char **input, char *d_name)
{
	if (**input != '*')
		return (0);
	skip_star(input);
	if (!**input)
		return (1);
	*start = *input;
	*match = d_name;
	return (0);
}

bool	match_char(char *input, char *d_name)
{
	char	*start;
	char	*match;

	start = input;
	match = d_name;
	if (!input)
		return (false);
	while (*d_name)
	{
		if (star_skip(&start, &match, &input, d_name))
			break ;
		if (reset(&input, &d_name, start, &match) == FAILUER)
			return (false);
		increment(&input, &match);
	}
	skip_star(&input);
	if (!*input)
		return (true);
	return (false);
}
