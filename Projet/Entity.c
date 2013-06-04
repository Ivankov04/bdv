#include "Entity.h"
#include <stdlib.h>
#include <unistd.h>

static void
entity_update (Entity *this);


Entity *
entity_new (void)
{
	Entity *this;

	if ((this = calloc(1, sizeof(Entity))) == NULL)
		return NULL;

	entity_init(this);

	return this;
}

void
entity_init (Entity *this)
{
    this->alive = TRUE;
    this->start = 0;
}

void
entity_main (Entity *this)
{
    while (this->alive)
    {
        usleep(1 * 1000);

        entity_update(this);
    }
}

static void
entity_update (Entity *this)
{

}

void
entity_free (Entity *entity)
{
	if (entity != NULL)
	{
		free (entity);
	}
}
