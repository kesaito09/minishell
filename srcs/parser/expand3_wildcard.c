/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3_wildcard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 03:49:39 by kesaitou          #+#    #+#             */
/*   Updated: 2025/11/23 14:37:15 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

void skip_star(char **wild_card_name)
{
	while (**wild_card_name && **wild_card_name == '*')
		(*wild_card_name)++;
}

int	match_char(char *wild_card_name, char *d_name)
{
	char	*start;
	char	*match;

	start = NULL;
	while (*d_name)
	{
		if (*wild_card_name == '*')
		{
			skip_star(&wild_card_name);
			if (!*wild_card_name)
				break;			
			start = wild_card_name;
			match = d_name;
		}
		if (*wild_card_name != *d_name)
		{
			if (!start)
				return (FAILUER);
			wild_card_name = start;
			d_name = (match++);
		}
        else
        {
            wild_card_name++;
            d_name++;
        }
	}
	skip_star(&wild_card_name);
	if (!*wild_card_name)
		return (SUCCESS);
	return (FAILUER);	
}

int check_hidden_file(char *wild_card_name)
{
	if (!wild_card_name)
		return (FAILUER);	
	if (wild_card_name[0] == '.')
		return (SUCCESS);
	return (FAILUER);
}

t_token	*token_dir(char *wild_card_name)
{
	DIR		*dp;
	t_token	*token_list;
	t_token	*token;
	t_dirent *dent;	

	token_list = NULL;
	if ((dp = opendir(".")) == NULL)
		return (NULL);
	while (1)
	{
		dent = readdir(dp);
		if (!dent)
			break ;
		if (!ft_strncmp(dent->d_name, "..", 2) || (check_hidden_file(wild_card_name) == FAILUER && !ft_strncmp(dent ->d_name, ".", 1)))
			continue ;
		if (match_char(wild_card_name, dent ->d_name) == FAILUER)
			continue ;
		token = t_lstnew(dent->d_name);
		if (!token)
			return (NULL);
		t_lstadd_back(&token_list, token);
	}
	closedir(dp);
	return (token_list);
}

// void	print_token2(t_token *node)
// {
// 	while (node)
// 	{
// 		ft_putendl_fd(node->token, 2);
// 		node = node->next;
// 	}
// }

// int main(void)
// {
// 	t_token *token_list = token_dir("*");
// 	t_token	*token_list2 = token_dir(".*");

// 	print_token2(token_list);
// 	printf("\n");
// 	print_token2(token_list2);
// }

// /*

// .       inode 22343,    d_type  4
// ..      inode 12815876, d_type  4
// .git    inode 4289828,  d_type  4
// libft   inode 8722694,  d_type  4
// .vscode inode 18846,    d_type  4
// Makefile        inode 18709,    d_type  8
// includes        inode 4318662,  d_type  4
// srcs    inode 8606477,  d_type  4
// minishell       inode 31658,    d_type  8

// // struct dirent {
// //                ino_t          d_ino;       /* Inode number */
// //                off_t          d_off;       /* Not an offset; see below */
// //                unsigned short d_reclen;    /* Length of this record */
// //                unsigned char  d_type;      /* Type of file; not supported
// //                                               by all filesystem types */
// //                char           d_name[256]; /* Null-terminated filename */

// M*kef*

/*
	Makefile
	*
	M   *   i   *
	seg1   seg2
	M		i






*/

// */