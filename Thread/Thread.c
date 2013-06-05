#include "Thread.h"
#include <stdlib.h>
#include <stdio.h>

Thread *
thread_new (void (* callback) (), void *arg)
{
	Thread *this = NULL;

	if ((this = (Thread *) malloc (sizeof(Thread))) == NULL)
		return NULL;

    this->callback = (void* (*)(void *)) callback;
    this->arg      = arg;

	return this;
}

void
thread_create (Thread *t)
{
    pthread_attr_t thread_attr;
    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&t->id, &thread_attr, t->callback, t->arg);
}

void
thread_join (Thread *t)
{
	if (pthread_join(t->id, NULL) != 0)
		printf("Erreur pthread_join (0x.8x)\n", t);
}

void
thread_exit (Thread *t)
{
	pthread_exit(NULL);
	thread_free(t);
}

void
thread_free (Thread *p)
{
	if (p != NULL)
	{
		free(p);
	}
}
