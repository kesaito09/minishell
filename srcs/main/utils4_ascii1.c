/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_ascii1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 11:05:31 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/25 15:51:15 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <termios.h>
#include "../../includes/main.h"

static void	print_gonn(void);
static void	print_kirua(void);
static void	print_mini(void);
static void	print_shell(void);

void	print_logo(void)
{
	int	i;

	i = 0;
	while (i < 14)
	{
		print_gonn();
		print_fire(i);
		print_mini();
		print_shell();
		print_fire(i);
		print_kirua();
		i++;
	}
}

static void	print_gonn(void)
{
	char		*str[14];
	static int	i;

	if (i > 13)
		return ;
	str[0] = "     |＼    ,､ ,          ";
	str[1] = "  ヽｰ┘   `ｰ' '  |/!       ";
	str[2] = "ヽ｀   __      _ /ｧ       ";
	str[3] = " ゝ    〉- ｀ｰ´--{/       ";
	str[4] = " ヽ こ〉1{;}  {;}|}  _fi  ";
	str[5] = "   ゝ., ,、 ー' ノ  f-'入 ";
	str[6] = "   r‐ 'i_ ー7   ト ' r '  ";
	str[7] = "  /l     `ｰ '   |ー‐'     ";
	str[8] = "  ij             !        ";
	str[9] = "  Y`ー-----r-ーー i       ";
	str[10] = "  } ＿____,! _ _＿l       ";
	str[11] = "      ET l  l T∃ __       ";
	str[12] = "i.⌒ヽ__,l   l___/  ヽ     ";
	str[13] = " ￣￣￣￣      ￣￣￣      ";
	ft_putstr_fd(str[i], 1);
	i++;
}

static void	print_kirua(void)
{
	char		*str[14];
	static int	i;

	if (i > 13)
		return ;
	str[0] = "    ､-､∧l ヽil∧";
	str[1] = "   i`ｰ-.i  / __ﾚァ";
	str[2] = " ＜´,.-     ､ ヽ  ＞";
	str[3] = " /'ｧｒ,!i ﾄ、j ,ヾ ヽ";
	str[4] = "    i-'、 {;}ヽ!,┐  ﾄ´";
	str[5] = "    ヽｰ ＿＿,ィ-'ヽ￣`";
	str[6] = "     /i´`ー'   ^＞ 、";
	str[7] = "    /.l        i !";
	str[8] = "   rf´〉      ,!V";
	str[9] = "   Y´￣￣￣ ｀´|{,j";
	str[10] = "   L＿＿__,＿＿__i_j";
	str[11] = "      i干 l  l 干l";
	str[12] = "   i.⌒ヽ_j  l___/⌒.i";
	str[13] = "    ￣￣￣    ￣￣￣";
	ft_putendl_fd(str[i], 1);
	i++;
}

static void	print_mini(void)
{
	char		*str[14];
	static int	i;

	if (i > 13)
		return ;
	str[0] = "       professional hunters'   ";
	str[1] = "                               ";
	str[2] = "                               ";
	str[3] = " ███▄ ▄███▓ ██▓ ███▄    █  ██▓ ";
	str[4] = "▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒";
	str[5] = "▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░";
	str[6] = "▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░ ";
	str[7] = "▒██▒   ░██▒░██░▒██░   ▓██░░██░▒";
	str[8] = "░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒";
	str[9] = "░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░";
	str[10] = "░      ░    ▒ ░   ░   ░ ░  ▒ ░░";
	str[11] = "       ░    ░           ░  ░   ";
	str[12] = "                               ";
	str[13] = "                               ";
	ft_putstr_fd(str[i], 1);
	i++;
}

static void	print_shell(void)
{
	char		*str[14];
	static int	i;

	if (i > 13)
		return ;
	str[0] = "                                       ";
	str[1] = "                                       ";
	str[2] = "                                       ";
	str[3] = " ██████  ██░ ██ ▓█████  ██▓     ██▓    ";
	str[4] = "██    ▒ ▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒    ";
	str[5] = " ▓██▄   ▒██▀▀██░▒███   ▒██░    ▒██░    ";
	str[6] = " ▒   ██▒░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░    ";
	str[7] = "██████▒▒░▓█▒░██▓░▒████▒░██████▒░██████▒";
	str[8] = " ▒▓▒ ▒ ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░";
	str[9] = " ░▒  ░ ░ ▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░";
	str[10] = "  ░  ░   ░  ░░ ░   ░     ░ ░     ░ ░   ";
	str[11] = "     ░   ░  ░  ░   ░  ░    ░  ░    ░  ░";
	str[12] = "                                       ";
	str[13] = "         by kesaitou natakaha          ";
	ft_putstr_fd(str[i], 1);
	i++;
}
