/*
 * Binary AVL Tree - Functions Definitions
 */

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include <stdio.h>	/* printf */
#include <unistd.h> /* ssize_t */

#include "binary_sorted_tree.h"

#define SPACE (7)

typedef enum
{
	LEFT,
	RIGHT,
	NUM_SONS
} children_e;

typedef struct node_s
{
	void *data;
	struct node_s *child[NUM_SONS];
	size_t height;
} node_t;

struct avl_tree
{
	node_t *root;
	int (*cmp_func)(const void *first, const void *second);
};

/******************************************************************************/
/******************************************************************************/

/* Used for AVLDestroy */
static void RemoveLeafs(node_t *root);

/* Used for AVLInsert */
static node_t *NodeInsert(node_t *root,
						  node_t *new_node,
						  int (*cmp_func)(const void *data1, const void *data2));

/* Used for AVLRemove */
static node_t *RecursiveRemove(node_t *root,
							   int (*cmp_func)(const void *, const void *),
					    	   const void *data);

/* Used for AVLCount */
static size_t CountNodes(node_t *root);

/* Used for AVLFind */
static void *RecursiveFind(node_t *node, 
						   int(*func)(const void *, const void *), 
						   const void *data);

/* Used for AVLForEach */
static int RecursiveForEach(node_t *node,
							avl_operation_t operation,
							const void *arg);

/* Used for AVLMultipleRemove */
static void RecursiveMultipleRemove(avl_t *tree, node_t *node,
								    int (*should_remove)(void *data, void *arg),
								    void *arg);

/* Like the AVLRemove function, without the balance, used the	*/
/* Recursive Multiple Remove function							*/
static void RegularRemove(avl_t *tree, const void *data);


/* Used for AVLTreeMultiFind function */

static void RecursiveMultiFind(node_t *node,
							   int (*is_match)(void *data, void *arg),
							   void *arg,
							   dll_t *list);


/*********************************** Balance **********************************/

/* Checks and executes the balance of the tree */
static node_t *TreeBalance(node_t *root,
						   int (*cmp_func)(const void *data1,
						   const void *data2));

/* Rotates Right when needed*/
static node_t *RightRotate(node_t *higher);

/* Rotates Left when needed*/
static node_t *LeftRotate(node_t *lower);


/****************************** General Functions *****************************/

/* Creates and initializes a new node */
static node_t *CreateNewNode(const void *data);

/* The maximum of two numbers */
static size_t Max(size_t n1, size_t n2);

/* Height of specifc node */
static size_t NodeHeight(node_t *node);

/* Finds the highest height between two node's children */
static ssize_t MaxChildHeight(node_t *node);

/* Gets the difference between the heights of two node's children */
static int GetDifference(node_t *node);

/* Gets the smalest element in a sub_tree */
static node_t *SmalestElements(node_t *root);

/* Prints te tree, simulator */
static void PrintTreeRecursive(node_t *root, int level);

/******************************************************************************/
/******************************************************************************/

avl_t *AVLCreate(int (*cmp_func)(const void *data1, const void *data2))
{
	avl_t *new_avl = NULL;

	assert(cmp_func);

	new_avl = (avl_t *)malloc(sizeof(avl_t));

	if (!new_avl)
	{
		return (NULL);
	}

	/* initialize struct */
	new_avl->cmp_func = cmp_func;
	new_avl->root = NULL;

	return (new_avl);
}

/******************************************************************************/

void AVLDestroy(avl_t *tree)
{
	RemoveLeafs(tree->root);
	
	free(tree);
	tree = NULL;
}

/******************************************************************************/

int AVLInsert(avl_t *tree, const void *data)
{
	node_t *new_node = NULL;

	assert(tree);

	new_node = CreateNewNode(data);

	if (!new_node)
	{
		return (1);
	}

	if (AVLIsEmpty(tree))
	{
		tree->root = new_node;
	}
	else
	{
		NodeInsert(tree->root, new_node, tree->cmp_func);
		tree->root = TreeBalance(tree->root, tree->cmp_func);
	}

	return (0);
}

/******************************************************************************/

void AVLRemove(avl_t *tree, const void *data)
{
	RecursiveRemove(tree->root, tree->cmp_func, data);
	tree->root = TreeBalance(tree->root, tree->cmp_func);
}

/******************************************************************************/

int AVLIsEmpty(const avl_t *tree)
{
	assert(tree);

	return (tree->root == NULL);
}

/******************************************************************************/

size_t AVLCount(const avl_t *tree)
{
	return (CountNodes(tree->root));
}

/******************************************************************************/

size_t AVLHeight(const avl_t *tree)
{
	assert(tree);

	return (tree->root->height - 1);
}

void *AVLFind(const avl_t *tree, const void *data)
{
	assert(tree);
	assert(data);

	return (RecursiveFind(tree->root, tree->cmp_func, data));
}

/******************************************************************************/

int AVLForEach(avl_t *tree, avl_operation_t operation, const void *arg)
{
	return (RecursiveForEach(tree->root, operation, arg));
}

/******************************************************************************/

void AVLTreeRemoveMultiple(avl_t *tree,
						   int (*should_remove)(void *data, void *arg),
						   void *arg)
{
	RecursiveMultipleRemove(tree, tree->root, should_remove, arg);
	tree->root = TreeBalance(tree->root, tree->cmp_func);
}

/******************************************************************************/

void AVLTreeMultiFind(avl_t *tree,
					  int (*is_match)(void *data, void *arg),
					  void *arg,
					  dll_t *list)
{
	RecursiveMultiFind(tree->root, is_match, arg, list);
}

/******************************************************************************/
/******************************************************************************

							  Utility Functions 
							**********************/

static void RemoveLeafs(node_t *root)
{
	if (root == NULL)
	{
		return;
	}

	RemoveLeafs(root->child[LEFT]);
	RemoveLeafs(root->child[RIGHT]);

	free(root);
	root = NULL;
}

/******************************************************************************/

static node_t *NodeInsert(node_t *root,
						  node_t *new_node,
						  int (*cmp_func)(const void *data1, const void *data2))
{
	assert(new_node);
	assert(cmp_func);

	if (root == NULL)
	{
		return (new_node);
	}

	if (0 < cmp_func(root->data, new_node->data))
	{
		root->child[LEFT] = NodeInsert(root->child[LEFT], new_node, cmp_func);
	}
	else
	{
		root->child[RIGHT] = NodeInsert(root->child[RIGHT], new_node, cmp_func);
	}

	root->height = 1 + MaxChildHeight(root);

	return (root);
}

/******************************************************************************/

static node_t *RecursiveRemove(node_t *root,
							   int (*cmp_func)(const void *, const void *),
					    	   const void *data)
{
	node_t *temp = NULL;
	
	if (root == NULL)
	{
		return (root);
	}

	if (0 < cmp_func(root->data, data))
	{
		root->child[LEFT] = RecursiveRemove(root->child[LEFT], cmp_func, data);
	}
	else if (0 > cmp_func(root->data, data))
	{
		root->child[RIGHT] = RecursiveRemove(root->child[RIGHT],
							 cmp_func, data);
	}
	else
	{
		if (root->child[LEFT] == NULL)
		{
			temp = root->child[RIGHT];
			free(root);
			return (temp);
		}
		else if (root->child[RIGHT] == NULL)
		{
			temp = root->child[LEFT];
			free(root);
			return (temp);
		}

		temp = SmalestElements(root->child[RIGHT]);
		root->data = temp->data;
		root->child[RIGHT] = RecursiveRemove(root->child[RIGHT],
							 cmp_func, temp->data);
	}

	root->height = 1 + MaxChildHeight(root);

	return (root);
}

/******************************************************************************/

static size_t CountNodes(node_t *node)
{
	size_t counter = 0;

	if (node == NULL)
	{
		return (0);
	}

	/* preorder traversal */

	counter += CountNodes(node->child[LEFT]);
	counter += CountNodes(node->child[RIGHT]);

	return (1 + counter);
}

/******************************************************************************/

static void *RecursiveFind(node_t *node, 
						   int(*func)(const void *, const void *), 
						   const void *data)
{
	void *found_data = NULL;

	if (node == NULL)
	{
		return (NULL);
	}

	if (0 < func(node->data, data))
	{
		found_data = RecursiveFind(node->child[LEFT], func, data);
	}
	else if (0 > func(node->data, data))
	{
		found_data = RecursiveFind(node->child[RIGHT], func, data);
	}
	else
	{
		found_data = node->data;
	}

	return (found_data);
}

/******************************************************************************/

static int RecursiveForEach(node_t *node, avl_operation_t operation,
							const void *arg)
{
	int status = 0;
	
	if (!node)
	{
		return (0);
	}
	
	status = operation(node->data, arg);
	
	if (1 == status)
	{
		return (status);
	}
	
	RecursiveForEach(node->child[LEFT], operation, arg);
	RecursiveForEach(node->child[RIGHT], operation, arg);

	return (0);	
}

/******************************************************************************/

static void RecursiveMultipleRemove(avl_t *tree, node_t *node,
								    int (*should_remove)(void *data, void *arg),
								    void *arg)
{
	if (!node)
	{
		return;
	}
	
	if (0 == should_remove(node->data, arg))
	{
		RegularRemove(tree, node->data);
	}

	RecursiveMultipleRemove(tree, node->child[LEFT], should_remove, arg);
	RecursiveMultipleRemove(tree, node->child[RIGHT], should_remove, arg);
	
	
}

static void RegularRemove(avl_t *tree, const void *data)
{
	RecursiveRemove(tree->root, tree->cmp_func, data);
}

/******************************************************************************/

static void RecursiveMultiFind(node_t *node,
							   int (*is_match)(void *data, void *arg),
							   void *arg,
							   dll_t *list)
{
	if (!node)
	{
		return;
	}

	RecursiveMultiFind(node->child[LEFT],is_match, arg, list);
	RecursiveMultiFind(node->child[RIGHT],is_match, arg, list);

	if (0 == is_match(node->data, arg))
	{
		DLLInsert(DLLBegin(list), node->data);
	}
}

/******************************************************************************

							  Balance Functions 
							**********************/


static node_t *TreeBalance(node_t *root,
						   int (*cmp_func)(const void *data1,
						   const void *data2))
{
	int difference = 0;

	if (root == NULL)
	{
		return (NULL);
	}

	root->child[LEFT] = TreeBalance(root->child[LEFT], cmp_func);
	root->child[RIGHT] = TreeBalance(root->child[RIGHT], cmp_func);

	difference = GetDifference(root);

	if (1 < difference && 0 <= GetDifference(root->child[LEFT]))
	{
		return RightRotate(root);
	}
	if (-1 > difference && 0 >= GetDifference(root->child[RIGHT]))
	{
		return LeftRotate(root);
	}
	if (1 < difference && 0 > GetDifference(root->child[LEFT]))
	{
		root->child[LEFT] = LeftRotate(root->child[LEFT]);
		
		return RightRotate(root);
	}
	if (-1 > difference && 0 < GetDifference(root->child[RIGHT]))
	{
		root->child[RIGHT] = RightRotate(root->child[RIGHT]);
		
		return LeftRotate(root);
	}

	root->height = 1 + MaxChildHeight(root);

	return (root);
}

/******************************************************************************/

static node_t *RightRotate(node_t *higher)
{
	node_t *lower = higher->child[LEFT];
	node_t *significant_child = lower->child[RIGHT];

	lower->child[RIGHT] = higher;
	higher->child[LEFT] = significant_child;

	higher->height = 1 + MaxChildHeight(higher);
	
	lower->height = 1 + MaxChildHeight(lower);

	return (lower);
}

/******************************************************************************/

static node_t *LeftRotate(node_t *higher)
{
	node_t *lower = higher->child[RIGHT];
	node_t *significant_child = lower->child[LEFT];

	lower->child[LEFT] = higher;
	higher->child[RIGHT] = significant_child;

	higher->height = 1 + MaxChildHeight(higher);
	
	lower->height = 1 + MaxChildHeight(lower);

	return (lower);
}

/******************************************************************************

							  General Functions 
							**********************/


static node_t *CreateNewNode(const void *data)
{
	node_t *new_node = NULL;

	assert(data);

	new_node = (node_t *)malloc(sizeof(node_t));

	if (!new_node)
	{
		return (NULL);
	}

	new_node->data = (void *)data;
	new_node->child[LEFT] = NULL;
	new_node->child[RIGHT] = NULL;
	new_node->height = 1;	/* For balance it's 1 so when there		*/
						 	/* are not children it is equal to zero	*/
	return (new_node);
}

/******************************************************************************/

static size_t Max(size_t n1, size_t n2)
{
	return ((n1 > n2) ? n1 : n2);
}

/******************************************************************************/

static size_t NodeHeight(node_t *node)
{
	if (NULL == node)
	{
		return (0);
	}

	return (node->height);
}

/******************************************************************************/

static ssize_t MaxChildHeight(node_t *node)
{
	return (Max(NodeHeight(node->child[LEFT]),
			NodeHeight(node->child[RIGHT])));
}

/******************************************************************************/

static int GetDifference(node_t *node)
{
	if (NULL == node)
	{
		return (0);
	}

	return (NodeHeight(node->child[LEFT]) - NodeHeight(node->child[RIGHT]));
}

/******************************************************************************/

static node_t *SmalestElements(node_t *root)
{
	if (root->child[LEFT] == NULL)
	{
		return (root);
	}

	return (SmalestElements(root->child[LEFT]));
}

/******************************************************************************/

static void PrintTreeRecursive(node_t *root, int level)
{ 
	int i = 0;
	
	if (!root)
	{ 
		return; 
	}

	level += SPACE; 
  
	PrintTreeRecursive(root->child[RIGHT], level); 
	printf("\n"); 
	
	for (i = SPACE; i < level; i++) 
	{
		printf(" ");
	} 
	
	printf("%d\n", *((int *)root->data)); 
	
	PrintTreeRecursive(root->child[LEFT], level); 
} 

void PrintTree (avl_t *tree)
{ 
	node_t *root = tree->root;
	
	PrintTreeRecursive(root, 0);
	
	printf("\n\n");
} 















