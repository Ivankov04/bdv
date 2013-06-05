#include "BureauDeVote.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

// Singleton
static BureauDeVote this;

void
bureau_init (int max_capacity)
{
	this.graph = graph_new();
    this.max_capacity = max_capacity;

    GraphVertex *entree      = graph_vertex_new(lieu_new(ENTREE_SORTIE,    0, 0,  1, NULL)),
                // Entre 4 et 6 secondes au secrétariat
				*secretariat = graph_vertex_new(lieu_new(SECRETARIAT,      4, 6,  1, NULL)),
				// Entre 5 et 8 secondes au bureau du président
				*bureau      = graph_vertex_new(lieu_new(BUREAU_PRESIDENT, 5, 8,  1, NULL)),
				*isoloirs    = graph_vertex_new(lieu_new(ISOLOIRS,         0, 0,  4, isoloirs_new())),
				// Entre 4 et 6 secondes chez l'assesseur
				*assesseur   = graph_vertex_new(lieu_new(ASSESSEUR,        4, 6,  1, NULL)),
				// Les portes mettent 2 secondes à se fermer avant chaque départ
				*ascenseur   = graph_vertex_new(lieu_new(ASCENSEUR,        2, 2,  2, ascenseur_new()));

	// Création du graphe
	graph_add_arc(this.graph, entree,      secretariat);
	graph_add_arc(this.graph, secretariat, ascenseur);
	graph_add_arc(this.graph, ascenseur,   bureau);
	graph_add_arc(this.graph, bureau,      ascenseur);
	graph_add_arc(this.graph, ascenseur,   isoloirs);
	graph_add_arc(this.graph, isoloirs,    ascenseur);
	graph_add_arc(this.graph, ascenseur,   assesseur);
	graph_add_arc(this.graph, assesseur,   entree);

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
bureau_main ()
{
    this.start = event_get_now();

    while (this.alive)
    {
        usleep(1 * 1000);
        this.now = event_get_now() - this.start;

        bureau_update();
    }
}

void
bureau_update ()
{
    if (event_update(this.entity_on_create))
    {
        // Une personne vient d'arriver

        // Ne pas dépasser la limite autorisée de personnes dans le bureau de vote
        if (bb_queue_get_length(this.entities) < this.max_capacity)
        {
            Entity *e = entity_new();
            bb_queue_add(this.entities, e);

            entity_make_alive(e);
        }

        else
        {
            printf("Bureau de vote : Trop d'entités dans le bureau (%d)\n", this.max_capacity);
        }
    }
}

