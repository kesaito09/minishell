/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 21:32:05 by natakaha          #+#    #+#             */
/*   Updated: 2026/01/18 12:10:49 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	print_token(t_token *token)
{
	while (token)
	{
		fprintf(stderr, "--TOKEN: %s  TYPE: %d--\n", token->token, token->type);
		token = token ->next;
	}
}
