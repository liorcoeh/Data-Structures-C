/*
 * Binary Search Tree - Functions Definitions
 * Non recursive
 */

#include <stdio.h>	/* printf()	*/
#include <stdlib.h> /* malloc(), free() */
#include <assert.h> /* assert() */

#include "binary_search_tree.h"

typedef enum
{
	LEFT,
	RIGHT,
	NUM_SONS
} children_e;

typedef struct bst_node
{
	struct bst_node *parent;
	struct bst_node *nodes[2];
	void *data;
} bst_node_t;

struct binary_search_tree
{
	bst_node_t root_stub;
	int (*cmp_func)(const void *data1, const void *data2, const void *param);
	void *param;
};

/******************************************************************************/

int PrintTreePostOrder(bst_t *tree);

/******************************************************************************/

bst_t *BSTCreate(int (*cmp_func)
				(const void *data1, const void *data2, const void *param),
				const void *param)
{
	bst_t *new_bst = NULL;
	
	assert(cmp_func);
	assert(param);
	
	new_bst = (bst_t *)malloc(sizeof(bst_t));
	
	if (!new_bst)
	{
		return (NULL);
	}
	
	new_bst->root_stub.parent = NULL;
	new_bst->root_stub.nodes[LEFT] = &(new_bst->root_stub);
	new_bst->root_stub.nodes[RIGHT] = NULL;
	new_bst->cmp_func = cmp_func;
	new_bst->param = &param;
	new_bst->root_stub.data = NULL;
	
	return (new_bst);
}

/******************************************************************************/

void BSTDestroy(bst_t *tree)
{
	bst_iter_t to_remove = NULL;
	bst_iter_t check = NULL;
	
	assert(tree);
	
	check = BSTBegin(tree);
	to_remove = check;
	
	/* Iterating Post-Order from BSTBegin */
	while (0 == BSTIsEmpty(tree))
	{
		/* If it's a leaf, remove it */
		if (NULL == check->nodes[LEFT] && NULL == check->nodes[RIGHT])
		{
			check = check->parent;
			BSTRemove(to_remove);	
		}
		
		/* If it is the element with highet value */
		else if (check->nodes[RIGHT] != NULL && check->nodes[RIGHT]->data == NULL)
		{
			check = check->parent;
			BSTRemove(to_remove);
		}
		
		/* Not a leaf, go down the branch till getting to a leaf */
		else
		{
			check = BSTNext(check);
		}
		to_remove = check;
	}
	
	/* Removing the bst struct and freeing the tree */
	free(tree);
	tree = NULL;
}

/******************************************************************************/

bst_iter_t BSTInsert(bst_t *tree, const void *data)
{
	bst_iter_t front_iter = NULL;
	bst_iter_t back_iter = NULL;
	bst_node_t *new_node = NULL;
	children_e direction = LEFT;
	
	assert(tree);
	assert(data);
	
	new_node = (bst_node_t *)malloc(sizeof(bst_node_t));
	
	if (!new_node)
	{
		return (NULL);
	}
	
	front_iter = tree->root_stub.nodes[LEFT];
	back_iter = &(tree->root_stub);
	
	/* Finding the right place to put the new node */
	while (NULL != front_iter && !BSTIsEqual(BSTEnd(tree), front_iter))
	{	
		back_iter = front_iter;

		if (LEFT == (tree->cmp_func)(data, BSTGetData(front_iter), tree->param))
		{
			direction = LEFT;
			front_iter = front_iter->nodes[direction];
		}
		else if (RIGHT == (tree->cmp_func)(data, BSTGetData(front_iter),
				 tree->param))
		{
			direction = RIGHT;
			front_iter = front_iter->nodes[direction];
		}
	}
	/* Initializing and inserting the new node								*/
	
	/* If the inserted node has the highest value it will point to the bst	*/
	/* Else it will be NULL													*/
	if (BSTIsEqual(BSTEnd(tree), front_iter))
	{
		new_node->nodes[RIGHT] = BSTEnd(tree);
		tree->root_stub.parent = new_node;
	}
	else
	{
		new_node->nodes[RIGHT] = NULL;
	}
	
	back_iter->nodes[direction] = new_node;
	new_node->parent = back_iter;
	new_node->nodes[LEFT] = NULL;
	
	new_node->data = (void *)data;
	
	return (new_node);
}

/******************************************************************************/

void BSTRemove(bst_iter_t current)
{
	bst_iter_t to_swap = current;
	children_e parent_direction = 0;
	
	/* Getting the direction the parent to the current is heading to */
	if (current->parent->nodes[LEFT] == current) /*is sameiter*****/
	{
		parent_direction = LEFT;
	}
	else
	{
		parent_direction = RIGHT;
	}
	
	/* There are no children */
	if (NULL == current->nodes[LEFT] && NULL == current->nodes[RIGHT])
	{
		current->parent->nodes[parent_direction] = NULL;
	}
	
	/* There are two children */
	else if (NULL != current->nodes[LEFT] && NULL != current->nodes[RIGHT])
	{
		to_swap = current->nodes[LEFT];
		
		while (NULL != to_swap->nodes[RIGHT])
		{
			to_swap = to_swap->nodes[RIGHT];
		}
		
		/* The last right doesn't have a LEFT (he is a leaf) */
		if (NULL == to_swap->nodes[LEFT])
		{
			/* If the one to swap in the son of the one to delete */
			if (current->nodes[LEFT] == to_swap)
			{
				to_swap->parent->nodes[RIGHT] = current->nodes[RIGHT];
				to_swap->nodes[LEFT] = NULL;
				to_swap->parent = current->parent;
			}
			else
			{
				to_swap->parent->nodes[RIGHT] = NULL;
				to_swap->nodes[LEFT] = current->nodes[LEFT];
				current->nodes[LEFT]->parent = to_swap;
				to_swap->parent = current->parent;
			}

			to_swap->nodes[RIGHT] = current->nodes[RIGHT];
			current->nodes[RIGHT]->parent = to_swap;
			current->parent->nodes[parent_direction] = to_swap;
		}
		/* The last right does have a LEFT of it's own */
		else
		{
			/* If the one to swap isn't the child of current */
			if (current->nodes[LEFT] != to_swap)
			{
				to_swap->parent->nodes[RIGHT] = to_swap->nodes[LEFT];
				to_swap->nodes[LEFT]->parent = to_swap->parent;
				to_swap->nodes[LEFT] = current->nodes[LEFT];
				current->nodes[LEFT]->parent = to_swap;
			}
			
			to_swap->nodes[RIGHT] = current->nodes[RIGHT];
			current->nodes[RIGHT]->parent = to_swap;
			to_swap->parent = current->parent;
			current->parent->nodes[parent_direction] = to_swap;
		}
	}
	
	/* There is one child on LEFT */
	else if (NULL != current->nodes[LEFT])
	{
		current->nodes[LEFT]->parent = current->parent;
		current->parent->nodes[parent_direction] = current->nodes[LEFT];
	}
	
	/* There is one child on RIGHT */
	else
	{
		current->nodes[RIGHT]->parent = current->parent;
		current->parent->nodes[parent_direction] = current->nodes[RIGHT];
	}
	
	free(current);
	current = NULL;
}

/******************************************************************************/

void *BSTGetData(const bst_iter_t current)
{
	return (current->data);
}

/******************************************************************************/

bst_iter_t BSTBegin(const bst_t *tree)
{
	bst_iter_t check = NULL;

	assert(tree);
	
	check = (bst_iter_t)&(tree->root_stub);
	
	if (BSTIsEmpty(tree))
	{
		return (check);
	}
	
	while (NULL != check->nodes[LEFT])
	{
		check = check->nodes[LEFT];
	}
		
	return (check);
}

/******************************************************************************/

bst_iter_t BSTEnd(const bst_t *tree)
{	
	assert(tree);
	
	return ((bst_iter_t )&(tree->root_stub));
}

/******************************************************************************/

bst_iter_t BSTNext(const bst_iter_t current)
{
	bst_iter_t next = NULL;
	
	assert(current);
	
	next = current->parent;
	
	/* If there is a RIGHT child */
	if (NULL != current->nodes[RIGHT])
	{
		next = current->nodes[RIGHT];
		
		/* In the case it is the highest value it will return the bst */
		if (next->data == NULL)
		{
			return (next);
		}
		
		/* While there are LEFT children in the branch */
		while (next->nodes[LEFT])
		{
			next = next->nodes[LEFT];
		}

		return (next);
	}
	
	/* If there is a LEFT parent, go on them until a RIGHT parent */
	else if (next->nodes[RIGHT] == current)
	{
		while (next->parent->nodes[RIGHT] == next)
		{
			next = next->parent;
		}
		
		return (next->parent);
	}

	return (next);
}

bst_iter_t BSTPrev(const bst_iter_t current)
{
	bst_iter_t prev = NULL;
	
	assert(current);
	
	prev = current->parent;
	
	/* If current is the bst */
	if (NULL == current->data)
	{
		return (prev);
	}
	
	/* If there is a LEFT child */
	if (NULL != current->nodes[LEFT])
	{
		prev = current->nodes[LEFT];
		
		/* While there are RIGHT children in the branch */
		while (prev->nodes[RIGHT])
		{
			prev = prev->nodes[RIGHT];
		}

		return (prev);
	}
	
	/* If there is a RIGHT parent, go on them until a LEFT parent */
	else if(prev->nodes[LEFT] == current)
	{
		while (prev->parent->nodes[LEFT] == prev)
		{
			prev = prev->parent;
		}
		
		return (prev->parent);
	}

	return (prev);
}


size_t BSTSize(const bst_t *tree)
{
	bst_iter_t check = NULL;
	size_t counter = 0;

	assert(tree);
	
	if (1 == BSTIsEmpty(tree))
	{
		return (0);
	}
	
	check = BSTBegin(tree);
	
	for (check = BSTBegin(tree); !BSTIsEqual(check, BSTEnd(tree));
		 check = BSTNext(check))
	{
		++counter;
	}
	
	return (counter);	
}

int BSTIsEmpty(const bst_t *tree)
{
	assert(tree);
	
	return (&(tree->root_stub) == tree->root_stub.nodes[LEFT]);
}

int BSTIsEqual(const bst_iter_t iter1, const bst_iter_t iter2)
{
	return (iter1 == iter2);
}

bst_iter_t BSTFind(bst_t *tree, const void *data)
{
	bst_iter_t check = NULL;
	children_e direction = LEFT;
	
	assert(tree);
	assert(data);
	
	check = tree->root_stub.nodes[LEFT];
	
	while (NULL != check && !BSTIsEqual(BSTEnd(tree), check))
	{		
		if (LEFT == (tree->cmp_func)(data, BSTGetData(check), tree->param))
		{
			direction = LEFT;
			check = check->nodes[direction];
		}
		else if (RIGHT == (tree->cmp_func)(data, BSTGetData(check), tree->param))
		{
			direction = RIGHT;
			check = check->nodes[direction];
		}
		/* The data in the element is equal to the searched data */
		else
		{
			return (check);
		}
	}
	
	/* Couldn't find a match */
	return (NULL);
}


int BSTForEach(const bst_iter_t from,
			   const bst_iter_t to,
			   int (*opr_func)(const void *, const void *),
			   const void *param)
{
	bst_iter_t iter = NULL;
	int status = 1;
	
	assert(opr_func);
	assert(param);
	
	for (iter = from; !BSTIsEqual(iter, to); iter = BSTNext(iter))
	{
		status = opr_func(iter->data, param);
		
		if (1 != status)
		{
			break;
		}
	}
	
	return (status);
}

/******************************************************************************/
/******************************************************************************/

int PrintTreePostOrder(bst_t *tree)
{
	bst_iter_t to_remove = NULL;
	bst_iter_t check = NULL;
	int root = 0;
	
	assert(tree);
	
	check = BSTBegin(tree);
	to_remove = check;
	
	/* Iterating Post-Order from BSTBegin */
	while (0 == BSTIsEmpty(tree))
	{
		/* If it's a leaf, remove it */
		if (NULL == check->nodes[LEFT] && NULL == check->nodes[RIGHT])
		{
			check = check->parent;
			printf("%d ,", *((int *)BSTGetData(to_remove)));
			BSTRemove(to_remove);	
		}
		
		/* If it is the element with highet value */
		else if (check->nodes[RIGHT] != NULL && check->nodes[RIGHT]->data == NULL)
		{
			check = check->parent;
			root = *((int *)BSTGetData(to_remove));
			printf("%d ,", *((int *)BSTGetData(to_remove)));
			BSTRemove(to_remove);
		}
		
		/* Not a leaf, go down the branch till getting to a leaf */
		else
		{
			check = BSTNext(check);
		}
		to_remove = check;
	}
	
	/* Removing the bst struct and freeing the tree */
	free(tree);
	tree = NULL;
	printf("\n\n");
	
	return (root);
}













