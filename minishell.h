/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 12:40:22 by kesaitou          #+#    #+#             */
/*   Updated: 2025/11/26 18:40:27 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/includes/ft_printf.h"
# include "libft/includes/get_next_line.h"
# include "libft/includes/libft.h"

typedef struct s_tree
{
	char			*op;
	struct s_tree	*left;
	struct s_tree	*right;

}					t_tree;


#endif