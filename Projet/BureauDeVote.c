#include "BureauDeVote.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

// Singleton
static BureauDeVote this;

void
bdv_init (int max_capacity)
{
    this.max_capacity = max_capacity;

    this.entree      = lieu_new(ENTREE_SORTIE,    0, 0, 1, LIEU_METHODS(entree));
    this.secretariat = lieu_new(SECRETARIAT,      4, 6, 1, NULL, NULL);                 // Entre 4 et 6 secondes au secrétariat
    this.bureau      = lieu_new(BUREAU_PRESIDENT, 5, 8, 1, NULL, NULL);                 // Entre 5 et 8 secondes au bureau du président
    this.isoloirs    = lieu_new(ISOLOIRS,         0, 0, 4, LIEU_METHODS(isoloirs));
    this.assesseur   = lieu_new(ASSESSEUR,        4, 6, 1, NULL, NULL);                 // Entre 4 et 6 secondes chez l'assesseur
    this.ascenseur   = lieu_new(ASCENSEUR,        2, 2, 2, LIEU_METHODS(ascenseur));    // Les portes mettent 2 secondes à se fermer avant chaque départ

	// Création de l'itinéraire
	this.chemin = malloc(sizeof(Lieu *) * PATH_SIZE);
    memcpy (
        this.chemin,
        (Lieu *[PATH_SIZE]) {
            this.entree,
            this.secretariat, this.ascenseur, // RDC->1er étage
            this.bureau,      this.ascenseur, // 1er étage->2ème étage
            this.isoloirs,    this.ascenseur, // 2ème étage->RDC
            this.assesseur,                   // RDC
            this.entree
        },
        sizeof(Lieu *) * PATH_SIZE
    );

	// Evenements
	// "Le délai séparant deux arrivées successives est une valeur aléatoire comprise entre 1 et 5 secondes."
	this.entity_on_create = event_new(1000, 5000);

	// Starters
	clock_t now = event_get_now();
	event_start(this.entity_on_create, now);

    // Liste des entités
    this.entities = bb_queue_new();

    // Tout est prêt à partir de ce point
	this.alive = TRUE;
}

void
bdv_main ()
{
    this.start = event_get_now();

    while (this.alive)
    {
        usleep(1 * 1000);
        this.now = event_get_now() - this.start;

        bdv_update();
    }
}

Lieu *
bdv_get_entity_lieu (Entity *entity)
{
    if (entity->id_path >= 0 && entity->id_path < PATH_SIZE)
        return this.chemin[entity->id_path];

    else
        return NULL;
}

void
bdv_give_path (Entity *e)
{
    if (e->ready)
    {
        Lieu *cur_lieu = bdv_get_entity_lieu(e);

        if (cur_lieu != NULL)
        {
            printf("(%lu) arrive dans %s\n", e->id, cur_lieu->nom);
            event_restart_now(&e->wakeup, 3000, 3000);
            e->ready = FALSE;
        }

        else
        {
            // L'entité est arrivée en dehors du chemin
            printf("%lu Arrivée!\n", e->id);
        }
    }
}

void
bdv_update ()
{
    // Gestion évènements
    if (event_update(this.entity_on_create))
    {
        // Une personne vient d'arriver
        // Ne pas dépasser la limite autorisée de personnes dans le bureau de vote
        if (bb_queue_get_length(this.entities) < this.max_capacity)
        {
            Entity *e = entity_new(this.chemin);
            bb_queue_add(this.entities,  e);
            lieu_add_entity(this.entree, e);
            entity_make_alive(e);
            bdv_give_path(e);
        }

        else
            applog("Bureau de vote : Trop d'entités dans le bureau (%d)", this.max_capacity);
    }

    // Gestion entités
    foreach_bbqueue_item (this.entities, Entity *e)
    {
        entity_lock(e);
        bdv_give_path(e);
        entity_unlock(e);
    }


    // Gestion lieux
    lieu_update(this.entree);
    lieu_update(this.secretariat);
    lieu_update(this.bureau);
    lieu_update(this.isoloirs);
    lieu_update(this.assesseur);
    lieu_update(this.ascenseur);
}
