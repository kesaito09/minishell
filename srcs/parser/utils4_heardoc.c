/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_heardoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 21:02:26 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/16 21:34:48 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static int		digit(int i)
{
	int	dig;

	dig = 0;
	while (i)
	{
		i /= 10;
		dig++;
	}
	return (dig);
}

static void	allocate_i(char *num, int i)
{
	int	d;

	d = digit(i) - 1;
	while (i)
	{
		num[d] = i % 10 + '0';
		i /= 10;
		d--;
	}
}

char	*heardoc_check(void)
{
	char	*file;
	char	*def;
	int		i;
	char	*num;

	file = NULL;
	def = ft_strdup(".heardoc_");
	i = 1;
	while (true)
	{
		num = (char *)ft_calloc(sizeof(char), digit(i) + 1);
		if (!num)
			return (free(def), NULL);
		allocate_i(num, i);
		file = ft_strjoin(def, num);
		free(num);
		if (!file)
			return (free(def), NULL);
		if (access(file, F_OK) == -1)
			break ;
		i++;
	}
	free(def);
	return (file);
}

//int	main(void)
//{
//	ft_putendl_fd(heardoc_check(), 1);
//}