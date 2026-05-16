/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 12:40:22 by kesaitou          #+#    #+#             */
/*   Updated: 2026/05/16 16:10:28 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"
# include "builtin_cmd.h"
# include "execution.h"
# include "expander.h"
# include "lexer.h"
# include "main.h"
# include "parser.h"

# define SUCCESS 1
# define FAILURE -1
# define END 0

#endif