/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_operate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:26:37 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/02 12:32:59 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/pipex.h"

void	tree_operator(t_tree *branch, t_pipe *info, pid_t pid)
{
	if (branch->b_type == PIPE)
		manage_pipe(branch, info, pid);
	if (branch->b_type == COMMAND)
		manage_cmd(branch, info, pid);
	if (branch->b_type == MY_COMMAND)
		manage_my_cmd(branch, info, pid);
	else
		return ;
}

/*tester*/

t_tree	*tree_new(char **cmd, char *fname, t_file_type ftype, t_type btype)
{
	t_tree *node;

	node = (t_tree *)ft_calloc(sizeof(t_tree), 1);
	node->parent = NULL;
	node->right = NULL;
	node->left = NULL;
	node->argv = cmd;
	node->flist->f_type = ftype;
	node->flist->file = fname;
	node->b_type = btype;
	return (node);
}

void	tree_add_left(t_tree **branch, t_tree *node)
{
	(*branch)->left = node;
	node->parent = (*branch);
}

void	tree_add_right(t_tree **branch, t_tree *node)
{
	(*branch)->right = node;
	node->parent = (*branch);
}

int main(int argc, char **argv, char **envp)
{
	t_tree	*tmp;
	t_tree	*branch;
	t_pipe	info;
	t_pidlist	*plist;
	char	*str;
	char	*null;
	char	**cmd;

	null = (char *)NULL;
	plist = pid_new(getpid());

	branch = tree_new(&null, null, NONE, PIPE);
	info = correct_info(argc, argv, envp);

	str = "ls -l";
	cmd = ft_split(str, ' ');
	tmp = tree_new(cmd, null, NONE, COMMAND);
	tree_add_left(&branch, tmp);

	str = "head";
	cmd = ft_split(str, ' ');
	tmp = tree_new(cmd, null, NONE, COMMAND);
	tree_add_right(&branch, tmp);

	tree_operator(branch, &info, 1);
	waitpid_plist(plist);
}
