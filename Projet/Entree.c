#include "Entree.h"
#include <stdlib.h>
#include <stdio.h>

Entree *
entree_new (Lieu *lieu)
{
	Entree *this;

	if ((this = malloc(sizeof(Entree))) == NULL)
		return NULL;

	entree_init(this, lieu);

	return this;
}

void
entree_init (Entree *this, Lieu *lieu)
{
    this->father = lieu;
}

void
entree_update (Entree *this)
{
    Lieu *entree = this->father;
    BbQueue *entities = entree->entities;

    while (bb_queue_get_length(entities))
    {
        Entity *e = bb_queue_pop(entities);

        entity_lock(e);
        e->etage = entree->etage;
        event_restart_now(&e->wakeup, entree->duree_min * 1000, entree->duree_max * 1000);
        entity_unlock(e);
    }
}

void
entree_free (Entree *entree)
{
	if (entree != NULL)
	{
		free (entree);
	}
}
