#pragma once

// ---------- Includes ------------
#include <pthread.h>


// ---------- Defines -------------


// ------ Class declaration -------
typedef struct _Thread
{
    pthread_t id;
    void * (*callback) (void *);
    void *arg;

}	Thread;


// --------- Constructors ---------

Thread *
thread_new (void (* callback) (void *), void *arg);


// ----------- Methods ------------

void
thread_create (Thread *t);

void
thread_exit (Thread *t);


// --------- Destructors ----------

void
thread_free 			(Thread *p);
