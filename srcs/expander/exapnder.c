/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exapnder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 20:24:47 by kesaitou          #+#    #+#             */
/*   Updated: 2025/12/22 21:40:04 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"




int expander(t_token **token_list, t_token	*envp)
{
	t_token *cur_list;

	cur_list = *token_list;
	while (cur_list)
	{
		if (expand_variables(&cur_list, envp) == FAILUER)
			return (FAILUER);
		if (expand_ifs(&cur_list) == FAILUER)
			return (FAILUER);
		
		
		
	}
	
	
		
}

/*
	トークン自体はレキサーで区切られる
	t_token *arglistにコマンドトークンが連結されていて、それを変数展開し、その結果を分割する
	あるコマンドノードのarglistに繋がってるすべてのリストに対して、
	変数が存在すれば展開、分割、パス展開、クォート除去処理をする
	

	VAR1="-l"
	VAR2=file3
	[ls $VAR1 file1 file2 $VAR2]

	それぞれのトークンに対してexpander処理をすえ
	[ls]
	[$VAR1]
	[file1]
	[file2]
	[$VAR2]






*/