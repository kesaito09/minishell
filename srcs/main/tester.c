/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 20:54:04 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/07 20:56:18 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"



void	print_token(t_token *lst)
{
	while (lst)
	{
		ft_putstr_fd(lst->token, 2);
		ft_putchar_fd(':', 2);
		lst = lst->next;
	}
	ft_putchar_fd('\n', 2);
}

void	print_flist(t_flist *flist)
{
	while (flist)
	{
		ft_putstr_fd(flist->file, 2);
		ft_putchar_fd(',', 2);
		ft_putnbr_fd(flist->f_type, 2);
		ft_putchar_fd(':', 2);
		flist = flist->next;
	}
	ft_putchar_fd('\n', 2);
}

void	print_split(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		ft_putendl_fd(cmd[i], 2);
		i++;
	}
}

void	print_tree(t_tree *branch)
{
	if (!branch)
		return ;
	if (branch->b_type == PIPE)
	{
		ft_putendl_fd("PIPE", 1);
		return ;
	}
	if (branch->b_type == MY_COMMAND)
		ft_putendl_fd("MY_CMD", 1);
	if (branch->b_type == COMMAND)
		ft_putendl_fd("CMD", 1);
	ft_putendl_fd("----cmd------", 1);
	print_split(branch->argv);
	ft_putendl_fd("----redirect------", 1);
	print_flist(branch->flist);
	ft_putchar_fd('\n', 1);
}

void	print_tree_rec(t_tree *branch)
{
	print_tree(branch);
	if (branch->left)
		print_tree_rec(branch->left);
	if (branch->right)
		print_tree_rec(branch->right);
}
