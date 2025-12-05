/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:49:03 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/05 14:22:01 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_flist	*flist_new(t_file_type ftype, char *fname)
{
	t_flist *flist;

	flist = (t_flist *)ft_calloc(sizeof(t_flist), 1);
	flist->f_type = ftype;
	flist->file = fname;
	flist->next = NULL;
	return (flist);
}

void	flist_add_back(t_flist **lst, t_flist *new)
{
	t_flist	*tmp;

	if (!lst)
		return ;
	tmp = *lst;
	if (!*lst)
	{
		*lst = tmp;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	free_flist(t_flist *lst)
{
	t_flist	*tmp;

	if (!lst)
		return;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		free(lst);
		lst = tmp;
	}
}

/*tester*/

//void	print_flist(t_flist *lst)
//{
//	if (!lst)
//		return ;
//	while (lst)
//	{
//		ft_putendl_fd(lst->file, 2);
//		lst = lst->next;
//	}
//}

//int main(void)
//{
//	t_flist	*lst;
//	t_flist	*tmp;

//	lst = flist_new(OUTFILE, "outfile");
//	tmp = flist_new(INFILE, "infile1");
//	flist_add_back(&lst, tmp);
//	tmp = flist_new(INFILE, "infile2");
//	flist_add_back(&lst, tmp);
//	tmp = flist_new(INFILE, "infile3");
//	flist_add_back(&lst, tmp);
//	tmp = flist_new(INFILE, "infile4");
//	flist_add_back(&lst, tmp);
//	print_flist(lst);
//	free_flist(lst);
//}