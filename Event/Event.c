#include "Event.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

Event *event_new (int ms_min, int ms_max)
{
	Event *this;

	if ((this = calloc(1, sizeof(Event))) == NULL)
		return NULL;

	event_init(this, ms_min, ms_max);

	return this;
}

void event_restart (Event **pthis, int ms_min, int ms_max, clock_t now)
{
    event_free(*pthis);
    Event *res = event_new(ms_min, ms_max);
    event_start(res, now);
    *pthis = res;
}

void event_restart_now (Event **pthis, int ms_min, int ms_max)
{
    clock_t now = event_get_now();
    event_restart(pthis, ms_min, ms_max, now);
}

void event_init (Event *this, int ms_min, int ms_max)
{
	this->ms_min = ms_min;
	this->ms_max = ms_max;
}

void event_start_now (Event *this)
{
    clock_t now = event_get_now();
    event_start(this, now);
}

void event_start (Event *this, clock_t now)
{
    int time_distance = this->ms_max - this->ms_min;
    int rand_time = ((float)rand() / RAND_MAX) * time_distance;

    this->start = now;
    this->tick = this->ms_min + rand_time;
}

clock_t event_get_now ()
{
    static struct tms buf;
    return (times(&buf) * 10);
}

bool event_update (Event *this)
{
    clock_t now = event_get_now();

    int elapsed = now - this->start;

    if (elapsed > this->ms_max)
        return TRUE;

    if (elapsed < this->ms_min)
        return FALSE;

    // If the event emits a signal, reset the start time for the next pulse
    bool res;

    if (res = event_pulse(this, elapsed))
        event_start(this, now);

    return res;
}


bool event_pulse (Event *this, int elapsed)
{
    return (elapsed > this->tick);
}

void event_free (Event *event)
{
	if (event != NULL)
	{
		free (event);
	}
}
