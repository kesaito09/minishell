/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_ascii2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 11:05:31 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/25 15:49:07 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <termios.h>
#include "../../includes/main.h"

void	print_fire(int i)
{
	char		*str[14];

	if (i > 13)
		return ;
	str[0] = "      .        .     .  ";
	str[1] = "     MM      .M         ";
	str[2] = "    MM    ,MM           ";
	str[3] = "   \"M     MM :          ";
	str[4] = "        YMM,            ";
	str[5] = " .    'MMM,       ,     ";
	str[6] = " M.    'MMM       .M    ";
	str[7] = "  MM,   ,MMM       ,MM  ";
	str[8] = "  MM,  MMMMMM'  ,MMMMM' ";
	str[9] = "   ,MMM.MMMMMMM.MMMMM,  ";
	str[10] = "    MMMMMMMMMMMMMMMMMM, ";
	str[11] = "  MMMMMMMMMMMMMMMMMM    ";
	str[12] = "  'MMMMMMMMMMMMMMMM'    ";
	str[13] = "   \"\" \"\" \"\" \"\" \"\"       ";
	ft_putstr_fd(str[i], 1);
}
