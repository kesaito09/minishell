/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 20:54:04 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/19 14:50:37 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



# include "../../includes/tester.h"
# include "../../includes/execution.h"

void	print_space(int i)
{
	while (i--)
		write(2, "    ", 4);
}

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
	ft_putchar_fd('\n', 2);
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
		ft_putendl_fd("CONNECTION:[&&]", 2);
		return ;
	}
	if (branch->b_type == DISJUNCTION)
	{
		print_space(i);
		ft_putendl_fd("CONNECTION:[||]", 2);
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
	if (branch ->b_type == SUBSHELL)
	{
		print_space(i);
		ft_putendl_fd("SUBSHELL[()]", 2);
	}
	print_space(i);
	ft_putendl_fd("ARGV", 2);
	if (branch ->argv)
		print_split(branch->argv, i);
	print_space(i);
	ft_putendl_fd("REDIRECT", 2);
	print_flist(branch->flist, i);
	ft_putchar_fd('\n', 2);
}

void	print_tree_rec(t_tree *branch)
{
	static int	i;

	print_tree(branch, i);
	if (branch->left)
	{
		print_space(++i);
		ft_putendl_fd("left------", 2);
		print_tree_rec(branch->left);
	}
	if (branch->right)
	{
		print_space(i);
		ft_putendl_fd("right------", 2);
		print_tree_rec(branch->right);
	}
}

void	print_token(t_token *cur)
{
	while (cur)
	{
		ft_putendl_fd(cur->token, 2);
		cur = cur->next;
	}
}

#include <stdio.h>
#include <stdbool.h>

// リダイレクトの型に応じた記号を返すヘルパー
const char *get_redir_symbol(t_file_type type)
{
    if (type == INFILE) return "<";
    if (type == OUTFILE) return ">";
    if (type == APPEND) return ">>";
    if (type == HEARDOC) return "<<";
    return "?";
}

void print_ast(t_tree *node, char *prefix, bool is_left)
{
    if (!node)
        return;

    // 現在のノードのラベル表示
    printf("%s%s", prefix, is_left ? "├── " : "└── ");
    
    if (node->b_type == PIPE) printf("[PIPE (|)]\n");
    else if (node->b_type == CONJUNCTION) printf("[AND (&&)]\n");
    else if (node->b_type == DISJUNCTION) printf("[OR (||)]\n");
    else if (node->b_type == SUBSHELL) printf("[SUBSHELL ( )]\n");
    else if (node->b_type == COMMAND || node->b_type == MY_COMMAND)
    {
        printf("[CMD: ");
        if (node->argv && node->argv[0])
            for (int j = 0; node->argv[j]; j++)
                printf("%s%s", node->argv[j], node->argv[j+1] ? " " : "");
        printf("]\n");
    }

    // 次の階層のためのインデント文字列を準備
    char new_prefix[256];
    snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_left ? "│   " : "    ");

    // リダイレクト情報があれば表示
    t_flist *curr_file = node->flist;
    while (curr_file)
    {
        printf("%s├── [REDIR: %s %s]\n", new_prefix, 
               get_redir_symbol(curr_file ->f_type), curr_file ->file);
        curr_file = curr_file->next;
    }

    // 枝の再帰
    if (node->b_type == SUBSHELL)
        print_ast(node->left, new_prefix, false);
    else
    {
        if (node->left)
            print_ast(node->left, new_prefix, true);
        if (node->right)
            print_ast(node->right, new_prefix, false);
    }
}

// 呼び出し用関数
void visualize_tree(t_tree *root, char *argv1)
{
    if (!root) return;
    printf("--- %s ---\n",argv1);
    // ルートはインデントなし、is_leftはfalseで開始
    print_ast(root, "", false);
    printf("-------------------------\n");
}