#include "Ascenseur.h"
#include <stdlib.h>

static bool
ascenseur_is_level(Ascenseur *this, int level);


Ascenseur *
ascenseur_new (Lieu *father)
{
	Ascenseur *this;

	if ((this = malloc(sizeof(Ascenseur))) == NULL)
		return NULL;

	ascenseur_init(this, father);

	return this;
}

void
ascenseur_init (Ascenseur *this, Lieu *father)
{
	this->level[0] = lieu_new(ETAGE_ASCENSEUR, 0, 3, 3, 2, NULL, NULL);
	this->level[1] = lieu_new(ETAGE_ASCENSEUR, 1, 3, 3, 2, NULL, NULL);
	this->level[2] = lieu_new(ETAGE_ASCENSEUR, 2, 3, 3, 2, NULL, NULL);
	this->cur = this->level[0];
	this->dest = NULL;

	this->father = father;
}

static bool
ascenseur_is_level(Ascenseur *this, int level)
{
    return ((this->cur == this->level[level])
          && this->dest == NULL);
}

static bool
ascenseur_plein (Ascenseur *this)
{
    return (bb_queue_get_length(this->entities_inside) > this->father->max_capacity);
}

void
ascenseur_update (Ascenseur *this)
{
    Lieu *asc = this->father;
    BbQueue *entities = asc->entities;

    // Gestion entités
    foreach_bbqueue_item(entities, Entity *e)
    {
        entity_lock(e);

        if (ascenseur_is_level(this, e->etage)
        && !ascenseur_plein(this))
        {
            // Ascenseur arrêté
            switch (e->etage)
            {
                case 0: // direction level 1
                    this->dest = this->level[1];
                break;

                case 1: // direction level 2
                    this->dest = this->level[2];
                break;

                case 2: // direction level 0
                    this->dest = this->level[0];
                break;
            }

            bb_queue_add(this->entities_inside, e);
        }

        // event_restart_now(&e->wakeup, asc->duree_min * 1000, asc->duree_max * 1000);
        entity_unlock(e);
    }

    // Lancer l'ascenseur ici
}

void
ascenseur_free (Ascenseur *ascenseur)
{
	if (ascenseur != NULL)
	{
		free (ascenseur);
	}
}
