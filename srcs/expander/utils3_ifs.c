/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_ifs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 23:03:55 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/21 06:24:29 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expander.h"

static t_ifs_state	is_ifs(char c, char *ifs);
static int			ifs_switcher(char c, char *ifs, t_ifs_state state);
static int			t_lstnew_add_back(t_token **lst, char *input, int i,
						t_token_type type);

int	ifs_split(char *input, char *ifs, t_token **lst, t_ifs_state state)
{
	int	len;
	int	flag;

	len = 0;
	while (true)
	{
		flag = ifs_switcher(input[len], ifs, state);
		if (flag >> STATE_CHANGE & 1)
			state = is_ifs(input[len], ifs);
		if (flag >> INCREMENT & 1)
			input++;
		if (flag >> LEN_INCREMENT & 1)
			len++;
		if (flag >> ADD_LST & 1)
			if (t_lstnew_add_back(lst, input, len,
					SUB_TOKEN_IFS) == FAILUER)
				return (t_lstclear(lst, free), FAILUER);
		if (flag >> FINISH & 1)
			return (t_lstsize(*lst));
		if (flag >> ADD_LST & 1)
		{
			input += len + 1;
			len = 0;
		}
	}
}

static t_ifs_state	is_ifs(char c, char *ifs)
{
	if (c == '\0')
		return (NLL);
	else if (ft_strchr(" \t\n", c))
		return (SPCE);
	else if (*ifs && ft_strchr(ifs, c))
		return (IFS);
	return (WORD);
}

static int	ifs_switcher(char c, char *ifs, t_ifs_state state)
{
	if (is_ifs(c, ifs) == SPCE)
	{
		if (state == WORD)
			return (1 << STATE_CHANGE | 1 << ADD_LST);
		return (1 << INCREMENT);
	}
	if (is_ifs(c, ifs) == IFS)
	{
		if (state != SPCE)
			return (1 << STATE_CHANGE | 1 << ADD_LST);
		return (1 << INCREMENT | 1 << STATE_CHANGE);
	}
	if (is_ifs(c, ifs) == WORD)
		return (1 << LEN_INCREMENT | 1 << STATE_CHANGE);
	if (is_ifs(c, ifs) == NLL && state != SPCE)
		return (1 << STATE_CHANGE | 1 << FINISH | 1 << ADD_LST);
	return (1 << FINISH);
}

int	t_lstnew_add_back(t_token **lst, char *input, int i, t_token_type type)
{
	t_token	*node;

	node = f_lstnew(ft_strndup(input, i), type);
	if (!node)
		return (FAILUER);
	t_lstadd_back(lst, node);
	return (SUCCESS);
}

char	*ifs_join(t_token **sub)
{
	t_token_type	type;
	char			*str;
	char			*tmp;

	if (!sub || !*sub)
		return (NULL);
	str = ft_strdup("");
	type = SUB_TOKEN_GENERAL;
	while (*sub && (type != SUB_TOKEN_IFS || (*sub)->type != SUB_TOKEN_IFS))
	{
		tmp = str;
		str = ft_strjoin(tmp, (*sub)->token);
		free(tmp);
		if (!str)
			return (NULL);
		type = (*sub)->type;
		(*sub) = (*sub)->next;
	}
	return (str);
}

// int	main(int ac, char **av)
//{
//	t_token	*node;

//	if (ac < 3)
//		return (1);
//	node = NULL;
//	ifs_expand(av[1], av[2], &node, STRT);
//	print_token(node);
//}
