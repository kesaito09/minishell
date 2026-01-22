/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_ifs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 23:03:55 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/23 05:23:54 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expander.h"

t_ifs_state	is_ifs(char c, char *ifs)
{
	if (c == '\0')
		return (NLL);
	else if (ft_strchr(" \t", c))
		return (SPCE);
	else if (*ifs && ft_strchr(ifs, c))
		return (IFS);
	return (WORD);
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


t_token	*ifs_insert(t_token *node, t_token *envp)
{
	char	*ifs;
	t_token	*lst;
	int		n;

	ifs = return_value("IFS", envp);
	if (!ifs)
		return (NULL);
	lst = NULL;
	if (ifs_split(node->token, ifs, &lst, STRT) == FAILUER)
		return (NULL);
	n = t_lstsize(lst);
	t_lstinsert(node, lst);
	node->type = SUB_TOKEN_IFS;
	return (t_lstmove(lst, n));
}

bool	has_type(t_token *sub, t_token_type type)
{
	while (sub)
	{
		if (sub->type == type)
			return (true);
		sub = sub->next;
	}
	return (false);
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
