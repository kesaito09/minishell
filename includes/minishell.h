/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 12:40:22 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/18 10:27:36 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"
# include "builtin_cmd.h"
# include "execution.h"
# include "lexer.h"
# include "main.h"
# include "parser.h"
# include "expander.h"

# define SUCCESS 1
# define FAILUER -1
# define END 0

void	print_token(t_token *token);

#endif