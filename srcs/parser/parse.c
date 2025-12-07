/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kesaitou <kesaitou@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 04:00:08 by kesaitou          #+#    #+#             */
/*   Updated: 2025/12/07 20:14:07 by kesaitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

/*
	[ls] [-l]
	のようにトークン分割されたコマンドを**argvにし、木にする必要がある
	ヒアドクが来たらflistを作る必要がある（複数対応する）
	それがファイルかどうかも判定する


*/

void	print_argv(char **argv)
{
	for (int i = 0; argv[i]; i++)
	{
		ft_printf("%s\n",argv[i]);
	}

	
	
}

static int	is_redirect(t_token *cur)
{
	return (cur->type == TOKEN_REDIRECT_IN || cur->type == TOKEN_REDIRECT_OUT
		|| cur->type == TOKEN_HEREDOC || cur->type == TOKEN_APPEND);
}

int	check_token(t_token *token, t_token_type type)
{
	if (!token)
		return (0);
	return (token->type == type);
}

/*
	リダイレクトの場合は次のトークンをファイルとして扱う


*/

/*
	argv :[ ls] [ -l ][ NULL]


*/
t_file_type	check_ftype(t_token *cur)
{
	if (cur ->type == TOKEN_REDIRECT_IN)
		return (INFILE);	
	if (cur ->type == TOKEN_REDIRECT_OUT)
	return (OUTFILE);				
	if (cur ->type == TOKEN_APPEND)
		return (APPEND);
	if (cur ->type == TOKEN_HEREDOC)
		return (HEARDOC);
	return (NONE);
}

int	is_builtin(char *token)
{
	if (!ft_strcmp(token, "cd") || !ft_strcmp(token, "env")
		|| !ft_strcmp(token, "export") || !ft_strcmp(token, "unset")
		|| !ft_strcmp(token, "echo") || !ft_strcmp(token, "pwd"))
		return (1);
	return (0);
}

void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

int	count_arr_elem(char **s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	**ultimate_strjoin(char **argv, char *new)
{
	char	**new_argv;
	int		arr_elem;
	int		i;

	if (!new)
		return (NULL);
	arr_elem = count_arr_elem(argv);
	new_argv = ft_calloc(arr_elem + 2, sizeof(char **));
	if (!new_argv)
		return (NULL);
	i = 0;
	while (i < arr_elem)
	{
		new_argv[i] = ft_strdup(argv[i]);
		if (!new_argv[i])
			return (free_argv(new_argv), NULL);
		i++;
	}
	new_argv[i + 1] = ft_strdup(new);
	if (!new_argv[i])
		return (free_argv(new_argv), NULL);
	return (new_argv);
}

void	append_redirect(t_tree *node, t_token ***curr)
{
	t_flist			*new_file;
	t_file_type		ftype;
	char			*fname;

	ftype = check_ftype(**curr);
	**curr = (**curr)->next;
	if ((**curr)->type == TOKEN_EOF)
		return ;
	fname = (**curr)->token;
	new_file = flist_new(ftype, fname);
	flist_add_back(&(node->flist), new_file);
	**curr = (**curr)->next;
}

void	append_argv(t_tree *node, t_token ***curr)
{
	char	**new_argv;

	new_argv = ultimate_strjoin(node->argv, (**curr)->token);
	print_argv(new_argv);
	if (!new_argv)
		return ;
	free_argv(node->argv);
	node->argv = new_argv;
	**curr = (**curr) ->next;
}

t_type	cmd_type(t_token *cur)
{
	if (is_builtin(cur->token))
		return (MY_COMMAND);
	return (COMMAND);
}

t_tree	*parse_command(t_token **cur)
{
	t_tree	*node;

	if (check_token(*cur, TOKEN_PIPE) || check_token(*cur, TOKEN_EOF))
		return (NULL);
	node = tree_new(NULL, NULL, cmd_type(*cur));
	while (*cur && !check_token(*cur, TOKEN_PIPE) && !check_token(*cur,
			TOKEN_EOF))
	{
		if (is_redirect(*cur))
			append_redirect(node, &cur);
		else
			append_argv(node, &cur);
	}
	return (node);
}

t_tree	*parse_pipeline(t_token **cur)
{
	t_tree	*left_node;
	t_tree	*pipe_node;

	left_node = parse_command(cur);
	if (!left_node)
		return (NULL);
	while (check_token(*cur, TOKEN_PIPE))
	{
		pipe_node = tree_new(NULL, NULL, PIPE);
		if (!pipe_node)
			return (NULL);
		pipe_node->left = left_node;
		*cur = (*cur)->next;
		pipe_node->right = parse_command(cur);
		// if (pipe_node ->left)
		// 	pipe_node ->left ->parent = pipe_node;
		// if (pipe_node ->right)
		// 	pipe_node -> right ->parent = pipe_node;
		left_node = pipe_node;
	}
	return (left_node);
}

t_tree	*parser(char *input)
{
	t_tree	*ast;
	t_token	*token_list;
	t_token	*cur_token;

	ast = NULL;
	token_list = NULL;
	lexer(input, &token_list);
	while (token_list)
	{
		printf(" WORD %s : TYPE ", token_list->token);
		printf("%u\n", token_list->type);
		token_list = token_list->next;
	}
	cur_token = token_list;
	ast = parse_pipeline(&cur_token);
	return (ast);
	
	
}


int main(void)
{
	t_tree	*ast;

	ast = parser("ls -l | cat -e");
	ft_putendl_fd(ast ->left ->argv[0], 1);




	
	
	
	
	
	
}