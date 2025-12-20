/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils7_expand_wildcard.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 03:49:39 by kesaitou          #+#    #+#             */
/*   Updated: 2025/12/20 09:30:07 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/minishell.h"

int	strchr_len(const char arg, char c)
{
	char	*ptr;

	ptr = ft_strchr(arg, c);
	return ((int)(ptr - arg));
}

int	match_char(char *wild_card_name, char *d_name)
{
	int	len;

	while (*wild_card_name)
	{
		len = strchr_len(wild_card_name, '*');
		if (!ft_strncmp(wild_card_name, d_name, len))
			return (SUCCESS);
		
	}
}

t_token	*tolken_dir(char *wild_card_name)
{
	DIR		*dp;
	t_token	*token_list;
	t_token	*token;

	token_list = NULL;
	if ((dp = opendir(".")) == NULL)
		return (NULL);
	while (1)
	{
		dent = readdir(dp);
		if (!dent)
			break ;
		if (!ft_strncmp(dent->d_name, ".", 1) || !ft_strncmp(dent->d_name, "..",
				2))
			continue ;
		match_char();
		token = t_lstnew(dent->d_name);
		if (!token)
			return (NULL);
		t_lstadd_back(&token_list, token);
	}
	closedir(dp);
	return (token_list);
}

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