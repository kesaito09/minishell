/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 20:54:04 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/09 20:39:56 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void	print_space(int i)
{
	while (i--)
		write(2, "    ", 4);
}

//void	print_token(t_token *lst)
//{
//	while (lst)
//	{
//		ft_putstr_fd(lst->token, 2);
//		ft_putchar_fd(':', 2);
//		lst = lst->next;
//	}
//	ft_putchar_fd('\n', 2);
//}

void	print_flist(t_flist *flist, int i)
{
	if (!flist)
	{
		print_space(i);
		ft_putendl_fd("NONE", 2);
	}
	while (flist)
	{
		print_space(i);
		ft_putstr_fd(flist->file, 2);
		ft_putchar_fd(',', 2);
		ft_putnbr_fd(flist->f_type, 2);
		ft_putchar_fd(':', 2);
		flist = flist->next;
	}
	ft_putchar_fd('\n', 2);
}

void	print_split(char **cmd, int j)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		print_space(j);
		ft_putstr_fd(cmd[i], 2);
		ft_putstr_fd(":", 2);
		i++;
	}
}

void	print_tree(t_tree *branch, int i)
{
	if (!branch)
		return ;
	if (branch->b_type == PIPE)
	{
		print_space(i);
		ft_putendl_fd("CONNECTION:[|]", 2);
		return ;
	}
	if (branch->b_type == CONJUNCTION)
	{
		print_space(i);
		ft_putendl_fd("CONNECTION:[||]", 2);
		return ;
	}
	if (branch->b_type == DISJUNCTION)
	{
		print_space(i);
		ft_putendl_fd("CONNECTION:[&&]", 2);
		return ;
	}
	if (branch->b_type == MY_COMMAND)
	{

		print_space(i);
		ft_putendl_fd("MY_CMD", 2);
	}
	if (branch->b_type == COMMAND)
	{
		print_space(i);
		ft_putendl_fd("CMD", 2);
	}
	print_space(i);
	ft_putendl_fd("ARGV", 2);
	print_split(branch->argv, i);
	ft_putendl_fd("|REDIRECT", 2);
	print_flist(branch->flist, i);
	ft_putchar_fd('\n', 2);
}

void	print_tree_rec(t_tree *branch)
{
	static int	i;

	i = 0;
	print_tree(branch, i);
	i++;
	if (branch->left)
	{
		ft_putendl_fd("left", 2);
		print_tree_rec(branch->left);
	}
	if (branch->right)
	{
		ft_putendl_fd("right", 2);
		print_tree_rec(branch->right);
	}
}
