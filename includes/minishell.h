/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 12:40:22 by kesaitou          #+#    #+#             */
/*   Updated: 2025/12/30 12:29:35 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"
# include "commands.h"
# include "lexer.h"
# include "readline.h"
# include "parser.h"
# include "expander.h"

# define SUCCESS 1
# define FAILUER -1
# define END 0

#endif