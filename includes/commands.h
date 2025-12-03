/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 17:58:04 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/03 03:00:29 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# define SUCCESS 1
# define FAILUER -1

#include "minishell.h"
# include <stdlib.h>

void	echo(char **cmd);
void	pwd(char **cmd);
void	cd(char **cmd);


#endif