/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 11:36:49 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/01 22:53:11 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/readline.h"

//int main(void)
//{
//	char	*line;

//	while (1)
//	{
//		line = readline("minishell$ ");
//		if (!line)
//			return (rl_clear_history(), 0);
//		add_history(line);
//		free(line);
//	}
//}

/*tester*/

t_flist	*flist_new(t_file_type ftype, char *fname)
{
	t_flist *flist;

	flist = (t_flist *)ft_calloc(sizeof(t_flist), 1);
	flist->f_type = ftype;
	flist->file = fname;
	flist->next = NULL;
	return (flist);
}

t_tree	*tree_new(char **cmd, char *fname, t_file_type ftype, t_type btype)
{
	t_tree *node;

	node = (t_tree *)ft_calloc(sizeof(t_tree), 1);
	node->parent = NULL;
	node->right = NULL;
	node->left = NULL;
	node->argv = cmd;
	node->flist = flist_new(ftype, fname);
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
	char	*str;
	char	*null;
	char	**cmd;

	null = (char *)NULL;

	branch = tree_new(&null, null, NONE, PIPE);
	info = correct_info(argc, argv, envp);

	str = "ls -l";
	cmd = ft_split(str, ' ');
	tmp = tree_new(cmd, null, NONE, COMMAND);
	tree_add_left(&branch, tmp);

	str = "cat -e";
	cmd = ft_split(str, ' ');
	tmp = tree_new(cmd, null, NONE, COMMAND);
	tree_add_right(&branch, tmp);

	tree_operator(tmp, &info, 1);
	waitpid_plist(info.plist);
}