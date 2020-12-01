/*
 * Singly Linked List - Functions Definitions
 */

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */

#include "singly_linked_list.h"

/* basic node for the linked list */
struct sll_node
{
	void *data;			   /* data to be stored */
	struct sll_node *next; /* pointer to next node */
};

typedef struct sll_node node_t;

/* basic linked list struct */
struct singly_linked_list
{
	node_t *head; /* pointer to the head of the list */
	node_t *tail; /* pointer to the tail of the list */
};

/*****************************************************************************/

/* utility function for new node creation */
static node_t *create_node(void *data);

sll_t *SLLCreate()
{
	sll_t *new_sll = (sll_t *)malloc(sizeof(sll_t)); /* make new list */
	node_t *dummy = create_node(NULL);			/* make the basic dummy node */

	/* check if one of the mallocs failed */
	if (new_sll == NULL) 
	{
		return (NULL);
	}
	
	if (dummy == NULL)
	{
		free(new_sll);
		return (NULL);
	}

	/* set the head and the tail of the list to point to the dummy */
	new_sll->tail = dummy;
	new_sll->head = dummy;

	/* assign the dummy data the list's adress */
	dummy->data = new_sll;

	return (new_sll);
}

/*****************************************************************************/

iterator_t SLLBegin(const sll_t *list)
{
	assert(NULL != list);

	return (list->head);
}

/*****************************************************************************/

iterator_t SLLInsert(iterator_t where, void *data)
{
	/* creating new node and assign it the values of current iterator where */
	node_t *new_node = create_node(where->data);

	assert(NULL != data);

	/* check if allocation failed */
	if (NULL == new_node)
	{
		while (NULL != where->next)
		{
			where = SLLNext(where);
		}
		
		return (where);
	}

	new_node->next = where->next;

	/* check if the iterator is the dummy, if so - update the list struct */
	if (where->next == NULL)
	{
		((sll_t *)where->data)->tail = new_node;
	}

	/* assign the new values to the iterator where */
	where->data = data;
	where->next = new_node;

	return (where);
}

/*****************************************************************************/

int SLLIsEmpty(const sll_t *list)
{
	assert(NULL != list);

	return ((list->head == list->tail) ? 1 : 0);
}

/*****************************************************************************/

void *SLLGetData(const iterator_t where)
{
	assert(NULL != where->next);

	return (where->data);
}

/*****************************************************************************/

size_t SLLCount(const sll_t *list)
{
	node_t *current = list->head;
	size_t counter = 0;

	assert(NULL != list);

	/* while we don't reach the end of the list */
	while (NULL != current->next)
	{
		++counter;
		current = current->next;
	}

	return (counter);
}

/*****************************************************************************/

iterator_t SLLNext(const iterator_t current)
{
	assert(NULL != current->next);

	return (current->next);
}

/*****************************************************************************/

iterator_t SLLEnd(const sll_t *list)
{
	assert(NULL != list);

	return (list->tail);
}

/*****************************************************************************/

int SLLIsSameIter(const iterator_t iter1, const iterator_t iter2)
{
	return (iter1 == iter2);
}

/*****************************************************************************/

iterator_t SLLRemove(iterator_t who)
{
	/* save the adress of the next node */
	node_t *temp_node = who->next;

	assert(NULL != who->next);

	/* assign the data and the next of the next node to current one */
	who->data = who->next->data;
	who->next = who->next->next;
	
	if (NULL == temp_node->next)
	{
		((sll_t *)temp_node->data)->tail = who;
	}

	/* free the next node */
	free(temp_node);
	temp_node = NULL;

	return (who);
}

/*****************************************************************************/

void SLLSetData(iterator_t iter, const void *data)
{
	assert(NULL != iter->next);

	iter->data = (void *)data;
}

/*****************************************************************************/

void SLLDestroy(sll_t *list)
{
	assert(NULL != list);
	/* loop through all the elements in list and free them until reachs *
	  * the end of the list												*/
	while ((!SLLIsEmpty(list)) && (NULL != SLLRemove(list->head)->next))
	{
		; /* empty loop */
	}

	/* free the dummy from the list */
	free(list->head);

	/* free the list struct itself */
	free(list);
	list = NULL;
}

/*****************************************************************************/

iterator_t SLLFind(const iterator_t from,
				   const iterator_t to,
				   const void *data,
                   int (*match_func)(void *, void *))
{
	iterator_t i = NULL; /* basic iterator to loop on */

	assert(NULL != data);
	assert(NULL != match_func);

	/* iterate the whole list */
	for (i = from; !SLLIsSameIter(i, to); i = SLLNext(i))
	{
		/* if there's a match return the iterator */
		if (match_func((void *)data, i->data))
		{
			return (i);
		}
	}

	/* if there wasn't matches return iterator at the 'to' argument */
	return (i);
}

/*****************************************************************************/

int SLLForEach(iterator_t from,
			   iterator_t to,
			   void *param,
			   int (*action_func)(void *param, void *data))
{
	iterator_t i = NULL; /* basic iterator to loop on 				 */
	int status = 0;		 /* status returned from the action function */

	assert(NULL != action_func);

	/* iterate the whole list and invoke the action function on each element */
	for (i = from; !SLLIsSameIter(i, to); i = SLLNext(i))
	{
		status = action_func(i->data, (void *)param);
	}

	return (status);
}

/*****************************************************************************/

void SLLAppend(sll_t *list1, sll_t *list2)
{
	/* Making the dummy of the first list equal the */
	/* first nod of the second list					*/
	SLLEnd(list1)->data = SLLBegin(list2)->data;
	SLLEnd(list1)->next = SLLBegin(list2)->next;
	
	/* Connecting the head struct of the first		*/
	/* list to the dummy struct of the second list	*/
	list1->tail = SLLEnd(list2);
	SLLEnd(list2)->data = list1;
	
	/* Deleting the head struct and the first node	*/
	/* of the second list							*/
	free(SLLBegin(list2));
	list2->head = NULL;
	free(list2);
	list2 = NULL;	
}

/*****************************************************************************/

void SLLFlip(sll_t *list)
{
	node_t *current_node = list->head;
	node_t *next_node = list->head->next;
	node_t *last_node = NULL;
	list->head->next = list->tail;

	while (NULL != next_node->next)
	{
		last_node = current_node;
		current_node = next_node;
		next_node = next_node->next;

		current_node->next = last_node;
	}

	list->head = current_node;
}

/*****************************************************************************/

int SLLHasLoop(const sll_t *list)
{
	node_t *one_step = list->head;
	node_t *two_steps = list->head;
	
	while (one_step && two_steps && two_steps->next)
	{
		one_step = one_step->next;
		two_steps = two_steps->next->next;
		
		if (one_step == two_steps)
		{
			return (1);
		}
	}
	
	return (0);
}

/*****************************************************************************/

iterator_t SLLFindIntersection(sll_t *list1, sll_t *list2)
{
	iterator_t iter1 = SLLBegin(list1);
	iterator_t iter2 = SLLBegin(list2);
	
	size_t count1 = SLLCount(list1);
	size_t count2 = SLLCount(list2);
	size_t counter = ((count1 >= count2) ? count1 - count2 : count2 - count1);
	size_t equal = ((count1 >= count2) ? count1 - counter : count2 - counter);
	
	if (count1 > count2)
	{
		for (iter1 = SLLBegin(list1); 0 != counter; iter1 = SLLNext(iter1))
		{
			--counter;
		}
	}
	else
	{
		for (iter2 = SLLBegin(list2); 0 != counter; iter2 = SLLNext(iter1))
		{
			--counter;
		}
	}
	
	for (counter = 0; counter < equal; ++counter)
	{
		if (iter1 == iter2)
		{
			return (iter1);
		}
		else
		{
			iter1 = SLLNext(iter1);
			iter2 = SLLNext(iter2);
		}
	}
	
	return (SLLEnd(list1));
	
	/*iterator_t iter1 = SLLBegin(list1);
	iterator_t iter2 = SLLBegin(list2);

	for (iter1 = SLLBegin(list1); !SLLIsSameIter(iter1, SLLEnd(list1));
		 iter1 = SLLNext(iter1))
	{
		for (iter2 = SLLBegin(list2); !SLLIsSameIter(iter2, SLLEnd(list2));
			 iter2 = SLLNext(iter2))
		{
			if(iter1 == iter2)
			{
				return (iter1);
			}
		}
	}
	
	return (0);*/
}

/*****************************************************************************/





/***** Utility Functions! *****/

static node_t *create_node(void *data)
{
	node_t *new_node = (node_t *)malloc(sizeof(node_t));

	/* check if allocation failed */
	if (NULL == new_node)
	{
		return (NULL);
	}

	new_node->data = data;
	new_node->next = NULL;

	return (new_node);
}



