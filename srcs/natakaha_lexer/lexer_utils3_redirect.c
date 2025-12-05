/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3_redirect.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:09:37 by natakaha          #+#    #+#             */
/*   Updated: 2025/12/05 16:39:33 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int	word_len(char *str)
{
	int	i;
	int	tmp;

	i = 0;
	while (str[i])
	{
		if (is_token_type(&str[i]) != TOKEN_WORD)
			return (i);
		if (is_quote(str[i]))
		{
			tmp = quote_len(&str[i]);
			if (tmp < 0)
				return (ERROR);
			i += tmp + 1;
		}
		i++;
	}
	return (i);
}

int	count_redirect(char *str)
{
	int	i;
	int	tmp;
	int	count;


}


//t_flist	*make_flist(char *str)
//{
//	t_file_type	ftype;
//	char		*fname;

//	if (is_token_type(str) == TOKEN_REDIRECT_OUT)
//		ftype = OUTFILE;
//	else if (is_token_type(str) == TOKEN_APPEND)
//		ftype = APPEND;
//	else if (is_token_type(str) == TOKEN_REDIRECT_IN)
//		ftype = INFILE;
//	else if (is_token_type(str) == TOKEN_HEREDOC)
//	{
//		fname =
//		ftype = INFILE
//	}

//}

int main(void)
{
	char *str;

	str = "abc\"|<\"<d e";
	printf("%s, %d\n",str, word_len(str));
}
