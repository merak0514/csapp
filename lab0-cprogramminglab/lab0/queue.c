/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    if (q != NULL){
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements? */
    /* Free queue structure */
    if (q == NULL) return;
    list_ele_t *h = q->head;
    if (h != NULL) {
        list_ele_t *tmp;
        while (h != NULL) {
            tmp = h->next;
            free(h);
            h = tmp;
        }
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_head(queue_t *q, int v)
{
    if(q == NULL) return false;
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) return false;
    newh->value = v;
    newh->next = q->head;
    if (q->head == NULL) q->tail = newh;
    q->head = newh;
    q->size ++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, int v)
{
    if (q==NULL) return false;
    list_ele_t* newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) return false;
    newh->value = v;
    newh->next = NULL;  // 重要

    if (q->head == NULL) {
        q->tail = newh;
        q->head = newh;
        q->size ++;
        return true;
    }else {
        q->tail->next = newh;
        q->tail = q->tail->next;
        q->size++;
        return true;
    }
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
bool q_remove_head(queue_t *q, int *vp)
{
    if (q == NULL) return false;
    if (q->head == NULL) return false;
    list_ele_t *tmp = q->head;
    if (vp != NULL) {
        *vp = tmp->value;
    }
    q->head = q->head->next;
    free(tmp);  // may cause some problem
    q->size --;
    if (q->head == NULL) {
        q->tail = NULL;
    }

    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL) return 0;
    return q->size;
}

/*
  Reverse elements in queue.

  Your implementation must not allocate or free any elements (e.g., by
  calling q_insert_head or q_remove_head).  Instead, it should modify
  the pointers in the existing data structure.
 */
void q_reverse(queue_t *q)
{
    if (q == NULL) return;
    if (q->head == NULL) return;
    q->tail = q->head;
    list_ele_t *current = q->head;
    list_ele_t *prev = NULL;
    list_ele_t *tmp = NULL;
    while(current != NULL) {
        tmp = current->next;
        current->next = prev;
        prev = current;
        current = tmp;
        if (current != NULL) {
            q->head = current;
        }
    }
}

