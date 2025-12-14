/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 04:00:08 by kesaitou          #+#    #+#             */
/*   Updated: 2025/12/10 00:42:11 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include "../../includes/parser.h"

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

t_file_type	check_ftype(t_token *cur)
{
	if (cur->type == TOKEN_REDIRECT_IN)
		return (INFILE);
	if (cur->type == TOKEN_REDIRECT_OUT)
		return (OUTFILE);
	if (cur->type == TOKEN_APPEND)
		return (APPEND);
	if (cur->type == TOKEN_HEREDOC)
		return (HEARDOC);
	return (NONE);
}

int	is_builtin(char *token)
{
	if (!ft_strcmp(token, "cd") || !ft_strcmp(token, "env") || !ft_strcmp(token,
			"export") || !ft_strcmp(token, "unset") || !ft_strcmp(token, "echo")
		|| !ft_strcmp(token, "pwd"))
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
	new_argv[i] = ft_strdup(new);
	if (!new_argv[i])
		return (free_argv(new_argv), NULL);
	return (new_argv);
}

void	append_redirect(t_tree *node, t_token **curr)
{
	t_flist		*new_file;
	t_file_type	ftype;
	char		*fname;

	ftype = check_ftype(*curr);
	*curr = (*curr)->next;
	if ((*curr)->type == TOKEN_EOF)
		return ;
	fname = (*curr)->token;
	new_file = flist_new(ftype, fname);
	flist_add_back(&(node->flist), new_file);
	*curr = (*curr)->next;
}

void	append_argv(t_tree *node, t_token **curr)
{
	char	**new_argv;

	new_argv = ultimate_strjoin(node->argv, (*curr)->token);
	if (!new_argv)
		return ;
	free_argv(node->argv);
	node->argv = new_argv;
	*curr = (*curr)->next;
}

t_tree_type	cmd_type(t_token *cur)
{
	if (is_builtin(cur->token))
		return (MY_COMMAND);
	return (COMMAND);
}

t_tree	*parse_command(t_token **cur)
{
	t_tree	*node;

	if (check_token(*cur, TOKEN_PIPE)
		|| check_token(*cur, TOKEN_EOF)
		|| check_token(*cur, TOKEN_CONJUNCTIONE)
		|| check_token(*cur, TOKEN_DISJUNCTIONE))
		return (NULL);
	node = tree_new(NULL, NULL, cmd_type(*cur));
	while (*cur
			&& !check_token(*cur, TOKEN_PIPE)
			&& !check_token(*cur, TOKEN_EOF)
			&& !check_token(*cur, TOKEN_CONJUNCTIONE)
			&& !check_token(*cur, TOKEN_DISJUNCTIONE))
	{
		if (is_redirect(*cur))
			append_redirect(node, cur);
		else
			append_argv(node, cur);
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
	while (*cur && check_token(*cur, TOKEN_PIPE))
	{
		pipe_node = tree_new(NULL, NULL, PIPE);
		if (!pipe_node)
		return (NULL);
		pipe_node->left = left_node;
		*cur = (*cur)->next;
		pipe_node->right = parse_pipeline(cur);
		if (!pipe_node->right)
		return (NULL);
		return (pipe_node);
	}
	return (left_node);
}

t_tree	*parse_logical(t_token **cur)
{
	t_tree	*logical_node;
	t_tree	*left_node;

	left_node = parse_pipeline(cur);
	if (!left_node)
	return (NULL);
	while (*cur && (check_token(*cur, TOKEN_CONJUNCTIONE) || (check_token(*cur,
		TOKEN_DISJUNCTIONE))))
		{
			if (check_token(*cur, TOKEN_CONJUNCTIONE))
			logical_node = tree_new(NULL, NULL, CONJUNCTION);
			else
			logical_node = tree_new(NULL, NULL, DISJUNCTION);
			logical_node->left = left_node;
			*cur = (*cur)->next;
			logical_node->right = parse_logical(cur);
			if (!logical_node->right)
			return (NULL);
			return (logical_node);
		}
		return (left_node);
}

void	print_lex(char *input, t_token *token)
{
	if (!token)
	return ;
	printf("%s\n", input);
	while (token)
	{
		printf(" WORD %s : TYPE ", token->token);
		printf("%u\n", token->type);
		token = token->next;
	}
}

t_tree	*parser(char *input)
{
	t_tree	*ast;
	t_token	*token_list;
	t_token	*cur_token;

	ast = NULL;
	token_list = NULL;
	if (!input || !*input)
		return (NULL);
	lexer(input, &token_list);
	cur_token = token_list;
	ast = parse_logical(&cur_token);
	t_lstclear(&token_list, free);
	return (ast);
}

//void	print_av(t_tree *ast)
//{
//	int	i;

//	if (!ast)
//	return ;
//	if (ast->argv)
//	{
//		i = 0;
//		while (ast->argv[i])
//		{
//			printf("ast%d %s \n", i, ast->argv[i]);
//			i++;
//		}
//		printf("\n");
//	}
//	print_av(ast->left);
//	print_av(ast->right);
//}

//int	main(void)
//{
//t_tree *ast1;
////t_tree *ast2;

//ast1 = parser("ls -l && cat -e || echo aaa");
//print_tree_rec(ast1);
// 	//ast2 = parser("ls -l | cat -e || wc -l && pwd | cat -e");
// 	//print_av(ast2);
//}

// t_tree	*parse_pipeline(t_token **cur)
// {
// 	t_tree	*left_node;
// 	t_tree	*pipe_node;

// 	left_node = parse_command(cur);
// 	if (!left_node)
// 		return (NULL);
// 	while (check_token(*cur, TOKEN_PIPE))
// 	{
// 		pipe_node = tree_new(NULL, NULL, PIPE);
// 		if (!pipe_node)
// 			return (NULL);
// 		pipe_node->left = left_node;
// 		*cur = (*cur)->next;
// 		pipe_node->right = parse_command(cur);
// 		// if (pipe_node ->left)
// 		// 	pipe_node ->left ->parent = pipe_node;
// 		// if (pipe_node ->right)
// 		// 	pipe_node -> right ->parent = pipe_node;
// 		left_node = pipe_node;
// 	}
// 	return (left_node);
// }