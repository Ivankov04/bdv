#pragma once

/* Dépendances */
#include <stdio.h>
#include <stdlib.h>

#ifdef BBQ_EXPORT_FUNCTION
	#ifdef WIN32
		#define EXPORT_FUNCTION __declspec(dllexport)
	#endif
#endif

#ifndef EXPORT_FUNCTION
	#define EXPORT_FUNCTION
#endif

/*
*   Working Macros
*/
/* BbChild */
#define __bb_child_get_next(child)	((child)->next)
#define __bb_child_get_prev(child)	((child)->prev)

/* BbQueue */
#define bb_queue_get_length(q)		  ((q)->len)
#define bb_queue_inc_length(q)		  ((q)->len++)
#define bb_queue_dec_length(q)		  ((q)->len--)
#define bb_queue_pick_last_child(q)	 ((q)->last)
#define bb_queue_pick_first_child(q)	((q)->first)

#define break_foreach					   	\
do {										\
	__child_foreach = (BbChild *) -1;	   	\
	continue;							   	\
} while (0)								   	\

#define foreach_bbqueue(queue, child)			   	\
	for (										   	\
		(child) = (queue)->first;					   \
		(child) != NULL;							  	\
		(child) = (child)->next						 \
	)											   	\

#define foreach_bbqueue_item(queue, item)					   \
	for (													   \
		BbChild *__child_foreach = (queue)->first,			  \
		*__bb_loop = 0;										 \
		__child_foreach != NULL;								\
		__child_foreach = (__child_foreach != (BbChild *)-1) ?  \
		 __child_foreach->next : NULL,						  \
		__bb_loop = (BbChild*)0								 \
	)														   \
		for (												   \
			item = __child_foreach->data;						\
			__bb_loop != (BbChild*) 1;						  \
			__bb_loop = (BbChild*) 1							\
		)													   \

#define is_last_bbqueue_item(queue)		\
	((__child_foreach == (queue)->last))

#define foreach_bbqueue_item_raw(queue, item)				   \
	for (													   \
		BbChild *__child_foreach = (queue)->first,			  \
		*__bb_loop = 0;										 \
		__child_foreach != NULL;								\
		__child_foreach = (__child_foreach != (BbChild *)-1) ?  \
		 __child_foreach->next : NULL,						  \
		__bb_loop = (BbChild*)0								 \
	)														   \
		for (												   \
			item = (int) __child_foreach->data;				\
			__bb_loop != (BbChild*) 1;						  \
			__bb_loop = (BbChild*) 1							\
		)													   \

#define foreach_bbqueue_item_reversed(queue, item)			  \
	for (													   \
		BbChild *__child_foreach = (queue)->last,				\
		*__bb_loop = 0;										 \
		__child_foreach != NULL;								\
		__child_foreach = (__child_foreach != (BbChild *)-1) ?  \
		 __child_foreach->prev : NULL,						  \
		__bb_loop = (BbChild*)0								 \
	)														   \
		for (												   \
			item = __child_foreach->data;					 \
			__bb_loop != (BbChild*) 1;						  \
			__bb_loop = (BbChild*) 1							\
		)													   \


#define foreach_bbqueue_item_reversed_raw(queue, item)			\
	for (													   	\
		BbChild *__child_foreach = (queue)->last,				\
		*__bb_loop = 0;										 	\
		__child_foreach != NULL;								\
		__child_foreach = (__child_foreach != (BbChild *)-1) ?  \
		 __child_foreach->prev : NULL,						  	\
		__bb_loop = (BbChild*)0								 	\
	)														   	\
		for (												   	\
			item = (int) __child_foreach->data;			 	\
			__bb_loop != (BbChild*) 1;						  	\
			__bb_loop = (BbChild*) 1							\
		)													   	\


#define bb_queue_add_array(queue, data, count)	  	\
do {													\
	int __array_counter;								\
	for (__array_counter = 0;					   	\
		 __array_counter < (count);				  	\
		 __array_counter++) {					   	\
		bb_queue_add((queue), (data)[__array_counter]);	\
	}											   	\
} while (0)										 	\

#define bb_queue_add_raw(queue, data) 		\
	(bb_queue_add(queue, (void*)(data)))

#define bb_queue_local_decl() \
{\
	.len = 0,\
	.first = NULL,\
	.last = NULL\
}

/**
*   Typedef
*/

typedef
struct _BbChild
{
	void *data;
	struct _BbChild *next,
					*prev;
}	BbChild;

typedef
struct _BbQueue
{
	int len;

	BbChild *first,
			*last;

}	BbQueue;

// --------- Constructors ---------
/* BbChild */
BbChild *
bb_child_new					(void *data);

/* BbQueue */
BbQueue *
bb_queue_new					(void);

BbQueue *
bb_queue_copy				   (BbQueue *queue);

void
bb_queue_init 					(BbQueue *q);

// ----------- Methods ------------

/* BbChild */
BbChild *
bb_child_get_next			   (BbChild *child);

BbChild *
bb_child_get_prev			   (BbChild *child);

void
bb_child_debug				  (BbChild *child);

void
bb_child_debug_string		   (BbChild *child);

void
bb_child_debug_integer		  (BbChild *child);

void
bb_child_debug_raw_integer	  (BbChild *child);

/* BbQueue */
	/*! Add */
void
bb_queue_add					(BbQueue *queue, void *data);
/* [head][][][][tail] <- [] */

void
bb_queue_push				   (BbQueue *queue, void *data);
/* [] -> [head][][][][tail] */

void
bb_queue_add_nth				(BbQueue *queue, void *data, int pos);
/* [head][] -> [nth] -> [][tail] */

	/*! Get : remove from the BbQueue and return the data */
void *
bb_queue_get_first			  (BbQueue *queue);
/* [head] <- [][][][tail] */

void *
bb_queue_pop					(BbQueue *queue);
/* [head][][][] -> [tail] */

void *
bb_queue_get_nth				(BbQueue *queue, int nth);
/* [head][] - - [nth] - -> [][tail] */

void *
bb_queue_replace_nth			(BbQueue *queue, void *data, int nth);

void
bb_queue_replace				(BbQueue *queue, void *data1, void *data2);

	/*!
		- Pick : Same as get, but prevent removing the child from the BbQueue
		- Accessors of the BbQueue on Read-Only
	*/
void *
bb_queue_pick_nth			   (BbQueue *queue, int pos);

void *
bb_queue_pick_first 			(BbQueue *queue);

void *
bb_queue_pick_last			  (BbQueue *queue);

	/*! Child Accessors : For optimizations */

void
bb_queue_add_child 				(BbQueue *queue, BbChild *c);

BbChild *
bb_queue_pick_child			 (BbQueue *queue, void *data);

BbChild *
bb_queue_pick_child_nth		 (BbQueue *queue, int nth);

	/*! Removal functions */
int
bb_queue_remv				   (BbQueue *queue, void *data);

void *
bb_queue_remv_nth			   (BbQueue *queue, int nth);

	/*! Debugging functions */
void
bb_queue_debug				  (BbQueue *queue);

void
bb_queue_debug_string		   (BbQueue *queue);

void
bb_queue_debug_integer		  (BbQueue *queue);

void
bb_queue_debug_custom		   (BbQueue *queue, void (*debug_function)());

void
bb_queue_debug_custom_data 		(BbQueue *queue, void (*debug_function)());

void
bb_queue_debug_raw_integer	  (BbQueue *queue);

	/*! Misc functions */

void
bb_queue_insert_after_child	 (BbQueue *queue, BbChild *before, void *data);

void
bb_queue_insert_before_child	(BbQueue *queue, BbChild *after, void *data);

void
bb_queue_insert_after		   (BbQueue *queue, void *after, void *data);

void
bb_queue_insert_before		  (BbQueue *queue, void *before, void *data);

void
bb_queue_switch				 (BbQueue *queue, void *data1, void *data2);

int
bb_queue_exists				 (BbQueue *queue, void *data);

void
bb_queue_do					 (BbQueue *queue, void (* do_func)());

void
bb_queue_do_enumerate		   (BbQueue *queue, void (* do_func)());

void
bb_queue_do_enumerate_data 		(BbQueue *q, void (*do_func)());

void
bb_queue_concat				 (BbQueue *queue_dest, BbQueue *queue);

void
bb_queue_concat_nth 			(BbQueue *q1, BbQueue *q2, int nth);

int
bb_queue_put_first 				(BbQueue *queue, void *data);

int
bb_queue_put_last 				(BbQueue *queue, void *data);

	/*! Sort functions */

void
bb_queue_bubble_sort	   		(BbQueue *queue);

// --------- Destructors ----------

/* BbChild */
void
bb_child_unref				  (BbChild *child);

/* BbQueue */
void
bb_queue_free				   (BbQueue *queue);

void
bb_queue_free_all			   (BbQueue *queue, void (*free_func)());

void
bb_queue_clear				  (BbQueue *queue);

#endif
