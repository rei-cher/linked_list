/**
 * Singly linked list header
 */

#ifndef LLIST_H
#define LLIST_H

/**
 * @brief A function pointer to a user defined function for freeing data stored
 *        in the linked list.
 */
typedef void (*free_f)(void *);

/**
 * @brief A function pointer to a user defined function for comparing/sorting
 *        the data in the linked list.
 */
typedef int (*comp_f)(const void *, const void *);

/**
 * @brief A function pointer to a user defined function for iterating on
 *        the data stored in the linked list.
 */
typedef void (*iter_f)(void *);

typedef struct llist llist_t;

/**
 * @brief creates new linked list
 *
 * @return a pointer to a linked list, else NULL
 */
llist_t * llist_create(void);

/**
 * @brief destroys a linked list
 *
 * @param pp_list the address of a linked list to be destroyed
 * @param p_free a pointer to a freeing function
 */
void llist_destroy(llist_t ** pp_list, free_f p_free);

/**
 * @brief queues a void pointer to the tail of a linked list
 *
 * @param p_list a pointer to the linked list
 * @param p_data a pointer to add to the tail of a linked list
 *
 * @return 0 on success, else 1
 */
int llist_enqueue(llist_t * p_list, void * p_data);

/**
 * @brief dequeues a void pointer from the head of a linked list
 *
 * @param p_list a pointer to the linked list
 *
 * @return a void pointer from the head of the linked list, else NULL
 */
void * llist_dequeue(llist_t * p_list);

/**
 * @brief pushes a void pointer to the head of a linked list
 *
 * @param p_list a pointer to the linked list
 * @param p_data a pointer to add to the head of a linked list
 *
 * @return 0 on success, else 1
 */
int llist_push(llist_t * p_list, void * p_data);

/**
 * @brief pops a void pointer from the head of a linked list
 *
 * @param p_list a pointer to the linked list
 *
 * @return a void pointer from the head of the linked list, else NULL
 */
void * llist_pop(llist_t * p_list);

/**
 * @brief peeks at the head void pointer of a linked list
 *
 * @param p_list a pointer to the linked list
 *
 * @return a void pointer from the head of the linked list, else NULL
 */
void * llist_peek(llist_t * p_list);

/**
 * @brief returns the number of elements in the linked list
 *
 * @param p_list a pointer to the linked list
 *
 * @return number of elements in the linked list, 0 for NULL or empty list
 */
int llist_size(llist_t * p_list);

/**
 * @brief checks the linked list for the provided data
 *
 * @param p_list a pointer to the linked list
 * @param p_data a pointer to the data to be searched for
 * @param p_comp a pointer to a user defined comparison function
 *
 * @return number of times the data is found in the linked list, else 0
 * @note this function checks the data stored in the pointer, not that the
 *       actual pointer is contained in the linked list, this function should
 *       return 0 if p_list, p_data, or p_comp are NULL
 */
int llist_contains(llist_t * p_list, void * p_data, comp_f p_comp);

/**
 * @brief performs user provided function on the data in the linked list
 *
 * @param p_list a pointer to the linked list
 * @param p_iter a pointer to a user defined function
 *
 * @return 0 on success, else 1
 */
int llist_iter(llist_t * p_list, iter_f p_iter);

/**
 * @brief sorts the linked list based on the provided function
 *
 * @param p_list a pointer to the linked list
 * @param p_comp a pointer to a user defined sort function
 *
 * @return 0 on success, else 1
 */
int llist_sort(llist_t * p_list, comp_f p_comp);

#endif

// end of llist.h
