#pragma once

// ---------- Includes ------------
#include <time.h>

#include "../Event/Event.h"

// ---------- Defines -------------
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#define bool char
#endif

// ------ Class declaration -------
typedef struct _Entity
{
    unsigned long int id;
	time_t start;
    bool alive;

}	Entity;


// --------- Constructors ---------

Entity *
entity_new (void);


// ----------- Methods ------------
void
entity_init (Entity *entity);

void
entity_main (Entity *entity);


bool
entity_is_dead (Entity *e);

// --------- Destructors ----------

void
entity_free (Entity *entity);


