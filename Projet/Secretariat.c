#include "Secretariat.h"
#include <stdlib.h>

Secretariat *
secretariat_new (Lieu *father)
{
	Secretariat *this;

	if ((this = malloc(sizeof(Secretariat))) == NULL)
		return NULL;

	secretariat_init(this, father);

	return this;
}


void
secretariat_init (Secretariat *this, Lieu *father)
{
	this->father = father;
}

void
secretariat_update (Secretariat *this)
{
    Lieu *sec = this->father;
    BbQueue *entities = sec->entities;

    while (bb_queue_get_length(entities))
    {
        Entity *e = bb_queue_pop(entities);

        entity_lock(e);
        e->etage = sec->etage;
        event_restart_now(&e->wakeup, sec->duree_min * 1000, sec->duree_max * 1000);
        entity_unlock(e);
    }
}

void
secretariat_free (Secretariat *secretariat)
{
	if (secretariat != NULL)
	{
		free (secretariat);
	}
}
