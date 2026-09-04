/**
 * Singly linked list.
 * Duplicate data should be accepted.
 * The linked list does not own any of the void pointers passed to it.
 * The free function is not mandatory when destroy is called.
 * The comparison function is mandatory for the contains and sort functions.
 * The iter function is mandatory for the iter function.
 */

#include <stdio.h>
#include <stdlib.h>

#include "llist.h"

typedef struct node node_t;

// struct that holds node data and next pointer
struct node
{
    struct node * p_next;
    void *        p_ptr;
};

// struct that holds the linked list elements
struct llist
{
    node_t * p_head;
    node_t * p_tail;
    int      size;
};

// TODO: static function prototypes here

llist_t * llist_create(void)
{
	llist_t * p_new_list = calloc(1, sizeof(llist_t));

	if (NULL == p_new_list)
	{
		goto END;
	}

	p_new_list->p_head = NULL;
	p_new_list->p_tail = NULL;
	p_new_list->size = 0;

END:
	return new_list;
}

void llist_destroy(llist_t ** pp_list, free_f p_free)
{
	void * p_data = 0;

	if ((NULL == pp_list) ||
		(NULL == * pp_list))
	{
		goto END;
	}
	
	while (0 < (* pp_list)->size)
	{
		p_data = llist_pop(* pp_data);

		if (NULL != p_free)
		{
			p_free(p_data);
		}
	}

	free(* pp_list);
	* pp_list = NULL;

END:
	return;

}

int llist_enqueue(llist_t * p_list, void * p_data)
{
	int SUCCESS = 1;

	if ((NULL == p_list) ||
		(NULL == p_data))
	{
		goto END;
	}

	node_t * p_new_node = calloc(1, sizeof(node_t));

	if (NULL == p_new_node)
	{
		goto END;
	}

	p_new_node->p_ptr = p_data;
	p_new_node->p_next = NULL;

	if (NULL == p_list->p_head)
	{
		p_list->p_head = p_new_node;
		p_list->p_tail = p_new_node;
	}
	else
	{
		p_list->p_tail->p_next = p_new_node;
		p_list->p_tail = p_new_node;
	}

	p_list->size++;

	SUCCESS = 0;

END:
	return SUCCESS;
}

void * llist_dequeue(llist_t * p_list)
{
	void * p_data = NULL;

	if ((NULL == p_list) ||
		(NULL == p_list->p_head))
	{
		goto END;
	}

	node_t * p_tmp = p_list->p_tail;
	p_data = p_tmp->p_ptr;

	node_t * p_prev = p_list->p_head;

	while (p_prev->p_next != p_tmp)
	{
		p_prev = p_prev->p_next;
	}

	p_list->p_tail = p_prev;
	p_list->p_tail->p_next = NULL;

END:
	return p_data;
}

int llist_push(llist_t * p_list, void * p_data)
{
	int SUCCESS = 1;

	if ((NULL == p_list) ||
		(NULL == p_data))
	{
		goto END;
	}

	node_t * p_new_node = calloc(1, sizeof(node_t));

	if (NULL == p_new_node)
	{
		goto END;
	}

	p_new_node->p_ptr = p_data;
	p_new_node->p_next = p_list->p_head;

	p_list->p_head = p_new_node;

	if (NULL == p_list->p_tail)
	{
		p_list->p_tail = p_new_node;
	}

	p_list->size++;

	SUCCESS = 0;

END:
	return SUCCESS;
}

void * llist_pop(llist_t * p_list)
{
	void * p_data = NULL;
	node_t * p_tmp = NULL;

	if ((NULL == p_list) &&
		(NULL == p_list->p_head))
	{
		goto END;
	}

	p_tmp = p_list->p_head;
	p_data = p_tmp->p_ptr;

	p_list->p_head = p_tmp->p_next;
	p_list->size--;

	if (NULL == p_list->p_head)
	{
		p_list->p_tail = NULL;
	}

	free(p_tmp);

END:
	return p_data;
}

void * llist_peek(llist_t * p_list)
{
	void * p_data = NULL;

	if ((NULL == p_list) ||
		(NULL == p_list->p_head))
	{
		goto END;
	}

	p_data = p_list->p_head->p_ptr;

END:
	return p_data;
}

int llist_size(llist_t * p_list)
{
	uint32_t size = 0;

	if (NULL == p_list)
	{
		goto END;
	}

	size = p_list->size;

END:
	return size;
}

int llist_contains(llist_t * p_list, void * p_data, comp_f p_comp)
{
    (void)p_list;
    (void)p_data;
    (void)p_comp;
    return 0;
}

int llist_iter(llist_t * p_list, iter_f p_iter)
{
    (void)p_list;
    (void)p_iter;
    return EXIT_FAILURE;
}

int llist_sort(llist_t * p_list, comp_f p_comp)
{
    (void)p_list;
    (void)p_comp;
    return EXIT_FAILURE;
}

// TODO: static function definitions here

// end of llist.c
