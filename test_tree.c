#include "minishell.h"
#include <stdio.h>

t_tree	*create_tree(void)
{
	t_tree	*tree;

	tree = malloc(sizeof(t_tree));
	if (!tree)
		return (NULL);
		
		
	tree->right = NULL;
	tree->op = "aaabbbbba";
}



void	create_left_child(t_tree *tree)
{
	tree ->left = create_tree();
}

int	main(void)
{
	t_tree *tree;

	tree = create_tree();
	create_left_child(&tree);
	tree ->left.
	
}