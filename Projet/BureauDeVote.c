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

    this.entree      = lieu_new(ENTREE_SORTIE,    0, 0, 0, 1, LIEU_METHODS(entree));
    this.secretariat = lieu_new(SECRETARIAT,      0, 4, 6, 1, LIEU_METHODS(secretariat));  // Entre 4 et 6 secondes au secrétariat
    this.bureau      = lieu_new(BUREAU_PRESIDENT, 1, 5, 8, 1, NULL, NULL);                 // Entre 5 et 8 secondes au bureau du président
    this.isoloirs    = lieu_new(ISOLOIRS,         2, 0, 0, 4, LIEU_METHODS(isoloirs));
    this.assesseur   = lieu_new(ASSESSEUR,        0, 4, 6, 1, NULL, NULL);                 // Entre 4 et 6 secondes chez l'assesseur
    this.ascenseur   = lieu_new(ASCENSEUR,        0, 2, 2, 2, LIEU_METHODS(ascenseur));    // Les portes mettent 2 secondes à se fermer avant chaque départ

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

clock_t
bdv_get_ticks ()
{
    return event_get_now() - this.start;
}

void
bdv_main ()
{
    this.start = event_get_now();

    while (this.alive)
    {
        usleep(10 * 1000); // 10ms de pause
        this.now = bdv_get_ticks();

        bdv_update();
    }
}

Lieu *
bdv_get_lieu (Entity *entity)
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
        Lieu *lieu = bdv_get_lieu(e);

        if (lieu != NULL)
        {
            applog("BureauDeVote", "Entité %lu arrive dans %s", e->id, lieu->nom);

            if (!lieu_plein(lieu))
            {
                e->ready = FALSE;
                lieu_add_entity(lieu, e);
            }

            else
            {
                applog("Lieu", "%s - plein à l'arrivée de Entité %lu", lieu->nom, e->id);
            }
        }

        else
        {
            // L'entité est arrivée en dehors du chemin
            e->alive = FALSE;
        }
    }
}

void
bdv_handle_events ()
{
    if (event_update(this.entity_on_create))
    {
        // Une personne vient d'arriver
        // applog("BureauDeVote", "Une personne veut rentrer");

        // Ne pas dépasser la limite autorisée de personnes dans le bureau de vote
        if (bb_queue_get_length(this.entities) < this.max_capacity)
        {
            Entity *e = entity_new(this.chemin);

            // On la rajoute à la liste des entitées du bureau
            bb_queue_add(this.entities,  e);

            // On rajoute l'entité dans le lieu
            lieu_add_entity(this.entree, e);

            // On démarre le thread de l'entité
            entity_make_alive(e);

            // On lui donne un chemin maintenant qu'elle est vivante
            bdv_give_path(e);
        }

        else
        {
            // applog("BureauDeVote", "Trop d'entités dans le bureau (%d)", this.max_capacity);
        }
    }
}

void
bdv_handle_entities ()
{
    // Liste chaînée d'entitées à supprimer
    static BbQueue to_delete = bb_queue_local_decl();

    // On vérifie l'état des entités et on le synchronise avec le bureau de vote
    foreach_bbqueue_item (this.entities, Entity *e)
    {
        /// Section critique
        entity_lock(e);

        if (entity_is_dead(e))
        {
            applog("BureauDeVote", "%lu - vient de sortir", e->id);
            bb_queue_add(&to_delete, e);
        }

        else
        {
            bdv_give_path(e);
        }

        entity_unlock(e);
        /// Fin section critique
    }

    while (bb_queue_get_length(&to_delete))
    {
        // On supprime les entités et on kill leur thread associé
        Entity *e = bb_queue_pop(&to_delete);
        entity_lock(e);
        entity_free(e);
    }
}

void
bdv_update ()
{
    // Gestion évènements
    bdv_handle_events();

    // Gestion entités
    bdv_handle_entities();

    // Gestion lieux
    lieu_update(this.entree);
    lieu_update(this.secretariat);
    lieu_update(this.bureau);
    lieu_update(this.isoloirs);
    lieu_update(this.assesseur);
    lieu_update(this.ascenseur);
}
