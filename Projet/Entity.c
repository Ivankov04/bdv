#include "Entity.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

static void entity_update (Entity *this);
static void entity_main (Entity *this);

static void entity_update (Entity *this)
{

}

static void entity_main (Entity *this)
{
    while (this->alive)
    {
        usleep(1000 * 1000);
        entity_update(this);
    }
}


Entity *entity_new (void)
{
	Entity *this;

	if ((this = malloc(sizeof(Entity))) == NULL)
		return NULL;

	entity_init(this);

	return this;
}

bool entity_died (Entity *this)
{
    if (this->alive == FALSE && this->start > 0);
}

void entity_init (Entity *this)
{
    this->alive = FALSE;
    this->start = 0;

    this->thread = thread_new((void(*)(void *))entity_main, this);
}

void entity_make_alive (Entity *this)
{
    this->start = event_get_now();
    this->alive = TRUE;

    thread_create(this->thread);
    printf("Entité thread=%x crée\n", (int) this->thread->id);
}

void entity_free (Entity *entity)
{
	if (entity != NULL)
	{
		free (entity);
	}
}
