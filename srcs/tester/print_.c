/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 21:32:05 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/17 16:54:37 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_sub_token(t_token *sub)
{
	while (sub)
	{
		ft_dprintf(2, "--SUB: %s   TYPE: %d--\n", sub ->token, sub ->type);
		sub = sub ->next;
	}
}

void	print_token(t_token *token)
{
	while (token)
	{
		ft_dprintf(2, "--TOKEN: %s  TYPE: %d--\n", token->token, token->type);
		if (token ->sub_token)
		{
			print_sub_token(token ->sub_token);
		}
		token = token ->next;
	}
}
