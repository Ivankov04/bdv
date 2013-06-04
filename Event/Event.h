#pragma once

// ---------- Includes ------------
#include <sys/times.h>

// ---------- Defines -------------
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#define bool char
#endif

// ------ Class declaration -------

typedef struct _Event
{
	int ms_min, ms_max;

	clock_t start;
	int tick;

}	Event;



// --------- Constructors ---------

Event *
event_new (int min, int max);


// ----------- Methods ------------
void
event_init (Event *event, int min, int max);

void
event_start (Event *this, clock_t now);

void
event_start_now (Event *this);

bool
event_pulse (Event *this, int elapsed);

bool
event_update (Event *this);

clock_t
event_get_now ();


// --------- Destructors ----------

void
event_free (Event *event);


