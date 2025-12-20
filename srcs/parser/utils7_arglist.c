/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7_arglist.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 02:58:10 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/20 12:20:38 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

int	append_token(t_tree *branch, t_token **cur)
{
	char	*copy;
	t_token	*node;

	copy = ft_strdup((*cur)->token);
	if (!copy)
		return (FAILUER);
	node = t_lstnew(copy);
	if (!node)
		return (free(copy), FAILUER);
	t_lstadd_back(&(branch->arg_list), node);
	*cur = (*cur)->next;
	return (SUCCESS);
}

char	**token_argv(t_token *node)
{
	char	**argv;
	int		i;
	t_token	*tmp;

	i = t_lstsize(node);
	argv = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	tmp = node;
	i = 0;
	while (tmp)
	{
		argv[i] = ft_strdup(tmp->token);
		if (!argv[i])
			return (free_split(argv), NULL);
		i++;
		tmp = tmp->next;
	}
	return (argv);
}

t_token	*argv_token(char **argv)
{
	t_token *node;
	t_token *lst;
	char *token;
	int i;

	i = 0;
	lst = NULL;
	while (argv[i])
	{
		token = ft_strdup(argv[i]);
		if (!token)
			return (t_lstclear(&lst, free), NULL);
		node = t_lstnew(token);
		if (!node)
			return (t_lstclear(&lst, free), NULL);
		t_lstadd_back(&lst, node);
		i++;
	}
	return (lst);
}

//void	print_split(char **cmd)
//{
//	int	i;

//	i = 0;
//	while (cmd[i])
//		ft_putendl_fd(cmd[i++], 2);
//}

//int	main(int ac, char **av, char **en)
//{
//	char	**cmd;
//	t_token	*node;

//	node = argv_token(en);
//	cmd = token_argv(&node);
//	print_split(cmd);
//	(void)ac;
//	(void)av;
//	(void)node;
//	(void)cmd;
//}