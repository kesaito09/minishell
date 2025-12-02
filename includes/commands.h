/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:58:04 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/01 23:03:19 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# define SUCCESS 1
# define FAIL -1

# include "pipex.h"
# include "readline.h"
# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/includes/libft.h"
# include <stdlib.h>

void	echo(char **cmd);
void	pwd(char **cmd);
void	cd(char **cmd);


#endif