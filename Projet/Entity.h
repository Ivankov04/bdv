#pragma once

// ---------- Includes ------------
#include "../Event/Event.h"
#include "../Thread/Thread.h"
#include "./Console.h"

// ---------- Defines -------------


// ------ Class declaration -------
typedef struct _Entity
{
    unsigned long int id;
	clock_t start;
    bool alive;
    bool ready;
    bool walking;

    int id_path;
    int etage;

    Thread *thread;
    Event *wakeup;

    pthread_mutex_t mutex;

}	Entity;


// --------- Constructors ---------
Entity *entity_new ();

// ----------- Methods ------------
void entity_init (Entity *entity);
void entity_make_alive (Entity *this);
bool entity_is_dead (Entity *this);


void entity_lock (Entity *this);
void entity_unlock (Entity *this);

// --------- Destructors ----------
void entity_free (Entity *entity);
