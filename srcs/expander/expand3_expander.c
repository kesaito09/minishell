/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 19:38:09 by kesaitou          #+#    #+#             */
/*   Updated: 2026/01/17 20:24:18 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/expander.h"

int	expander(t_token **node, t_shared_info *info, t_list_type type)
{
	//if (get_sub_token(node) == FAILUER)
	//	return (deep_token_clear(*node), FAILUER);
	(void)info;
	if (wildcard_expand(node, type) == FAILUER)
		return (deep_token_clear(*node), FAILUER);
	return (SUCCESS);
}
