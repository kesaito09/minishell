#include "minishell.h"
#include <stdio.h>
/*

	typedef struct s_tree
	{
		char			*op;
		struct s_tree	*left;
		struct s_tree	*right;

	}					t_tree;

	オペレーターが演算子
	文字列の中から演算子（キーワード）を探索し、オペレーターを親にしてオペランドを子にとる

	オペレーターが来たら左右の子供を探索する。左の子も存在するとは限らない
	右の子は次のオペレーターが来るまで探索する。
	
	-エラー条件
	オペレーターに対して子供が２つ存在しない

	オペレータが存在しないケース


	その時点の親の


*/




t_tree	*create_node(void)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node ->left = NULL;
	node->right = NULL;
	node->op = NULL;
	return (node);
}

t_tree	*create_tree(t_tree *tree, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		tree 
	}
	
	
	
	
	
	
}

void	store_child(t_tree *tree)
{
	
	
	
}

int	count_op(char *input)
{
	int	cnt;

	cnt = 0;
	while (*input)
	{
		if (*input == '|' || *input == '>')
		{
			cnt++;
		}
		input++;
	}
	return (cnt);
}

int	serach_op(char *input, t_tree *tree)
{
	while (*input)
	{
		if (*input == '|')
		{
			store_child()
		}
		else if (*input == '>')
		{

		}
	

		
	}
	
	
	
	
	
}

int	main(void)
{
	t_tree *tree;
	char	*test1 = "grep -v aaaa | cat -e | cat > outfile";


	
	
	
	
	tree = create_tree();
	create_left_child(tree);
	create_left_child(tree ->left);
	printf("%s",tree ->left ->left ->op);
	
}