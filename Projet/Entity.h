#pragma once

// ---------- Includes ------------
#include "../Event/Event.h"
#include "../Thread/Thread.h"

// ---------- Defines -------------


// ------ Class declaration -------
typedef struct _Entity
{
    unsigned long int id;
	clock_t start;
    bool alive;

    Thread *thread;

}	Entity;


// --------- Constructors ---------
Entity *entity_new (void);

// ----------- Methods ------------
void entity_init (Entity *entity);
void entity_make_alive (Entity *this);
bool entity_is_dead (Entity *e);

// --------- Destructors ----------
void entity_free (Entity *entity);
