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

#include "../includes/commands.h"
#include "../includes/pipex.h"

static void	treat_pipe_left(t_tree *branch, t_pipe *info, pid_t pid, t_pid **plist)
{
	if (manage_fd(info) == FAIL)
		return (perror(""));
	pid = fork();
	if (pid < 0)
		return (perror(""));
	if (pid == 0)
		tree_operator(branch->left, *info, pid, plist);
	close(info->fd_in[0]);
	close(info->fd_in[1]);
	close(info->fd_out[0]);
	pid_add_back(plist, pid);
}

static void	treat_pipe_right(t_tree *branch, t_pipe *info, pid_t pid, t_pid **plist)
{
	if (branch->right->state == PIPE)
		tree_operator(branch->right, *info, pid, plist);
	if (fd_stdout(info) == FAIL)
		return (perror(""));
	pid = fork();
	if (pid < 0)
		return (perror(""));
	if (pid == 0)
		tree_operator(branch->right, *info, pid, plist);
	close(info->fd_in[1]);
	pid_add_back(plist, pid);
}

static void	manage_pipe(t_tree *branch, t_pipe info, pid_t pid, t_pid **plist)
{
	if (pid == 0)
		exit(0);
	treat_pipe_left(branch, &info, pid, plist);
	ft_putnbr_fd(info.fd_out[0], 2);
	treat_pipe_right(branch, &info, pid, plist);
	ft_putnbr_fd(info.fd_in[0], 2);
	return ;
}

void	tree_operator(t_tree *branch, t_pipe info, pid_t pid, t_pid **plist)
{
	if (branch->state == PIPE)
		manage_pipe(branch, info, pid, plist);
	if (branch->state == COMMAND)
		manage_cmd(branch, info, pid, plist);
	if (branch->state == MY_COMMAND)
		manage_my_cmd(branch, info, pid, plist);
	else
		return ;
}

void	waitpid_plist(t_pid *plist)
{
	int	status;

	while (1)
	{
		plist = plist->next;
		if (!plist)
			return ;
		waitpid(plist->pid, &status, 0);
	}
}

/*tester*/

static t_tree	*tree_new(char **cmd, char *redirect_in, char *append,
		char *redirect_out, t_type state)
{
	t_tree *node;

	node = (t_tree *)ft_calloc(sizeof(t_tree), 1);
	node->op = NULL;
	node->right = NULL;
	node->left = NULL;
	node->argv = cmd;
	node->redirect_in = redirect_in;
	node->redirect_out = redirect_out;
	node->append = append;
	node->state = state;
	return (node);
}

void	tree_add_left(t_tree **branch, t_tree *node)
{
	(*branch)->left = node;
	node->op = (*branch);
}

void	tree_add_right(t_tree **branch, t_tree *node)
{
	(*branch)->right = node;
	node->op = (*branch);
}

int main(int argc, char **argv, char **envp)
{
	t_tree	*tmp;
	t_tree	*branch;
	t_pipe	info;
	t_pid	*plist;
	char	*str;
	char	*null;
	char	**cmd;

	null = (char *)NULL;
	plist = pid_new(getpid());

	branch = tree_new(&null, null, null, null, PIPE);
	info = correct_info(argc, argv, envp);

	str = "ls -l";
	cmd = ft_split(str, ' ');
	tmp = tree_new(cmd, null, null, null, COMMAND);
	tree_add_left(&branch, tmp);

	str = "head";
	cmd = ft_split(str, ' ');
	tmp = tree_new(cmd, null, null, null, COMMAND);
	tree_add_right(&branch, tmp);

	tree_operator(branch, info, 1, &plist);
	waitpid_plist(plist);
}
