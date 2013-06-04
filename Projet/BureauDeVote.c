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

    GraphVertex *entree      = graph_vertex_new(),
				*secretariat = graph_vertex_new(),
				*bureau      = graph_vertex_new(),
				*isoloirs    = graph_vertex_new(),
				*assesseur   = graph_vertex_new(),
				*ascenseur   = graph_vertex_new();

	// Création du graphe
	graph_add_arc(this.graph, entree, secretariat);
	graph_add_arc(this.graph, secretariat, ascenseur);
	graph_add_arc(this.graph, ascenseur, bureau);
	graph_add_arc(this.graph, bureau, ascenseur);
	graph_add_arc(this.graph, ascenseur, isoloirs);
	graph_add_arc(this.graph, isoloirs, ascenseur);
	graph_add_arc(this.graph, ascenseur, assesseur);
	graph_add_arc(this.graph, assesseur, entree);

	// Association des données aux vertices
	entree->user_data      = lieu_new(ENTREE_SORTIE,    0, 0,  1);
	secretariat->user_data = lieu_new(SECRETARIAT,      4, 6,  1);  // Entre 4 et 6 secondes au secrétariat
	bureau->user_data      = lieu_new(BUREAU_PRESIDENT, 5, 8,  1);  // Entre 5 et 8 secondes au bureau du président
	isoloirs->user_data    = lieu_new(ISOLOIRS,         0, 0,  4);
	assesseur->user_data   = lieu_new(ASSESSEUR,        4, 6,  1);  // Entre 4 et 6 secondes chez l'assesseur
	ascenseur->user_data   = lieu_new(ASCENSEUR,        2, 2,  2);  // Les portes mettent 2 secondes à se fermer avant chaque départ

	// Ascenseur et Isoloirs sont des classes héritant de Lieu
	lieu_set_data(ascenseur->user_data, ascenseur_new());

	// Evenements
	// "Le délai séparant deux arrivées successives est une valeur aléatoire comprise entre 1 et 5 secondes."
	this.entityOnCreate = event_new(1000, 5000);

	// Starters
	clock_t now = event_get_now();
	event_start(this.entityOnCreate, now);

    /* Mémoire partagée */
    int mem_descriptor;

    if ((mem_descriptor = shm_open("/list_entities", O_CREAT | O_RDWR, 0600)) < 0)
    {
        perror("list_entities");
        exit(EXIT_FAILURE);
    }

    if (ftruncate(mem_descriptor, sizeof(this.entities)) == -1)
    {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    this.entities = mmap(NULL, sizeof(BbQueue), PROT_READ | PROT_WRITE, MAP_SHARED, mem_descriptor, 0);
    bb_queue_init(this.entities);

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

    // Cleaning
    shm_unlink("/list_entities");
}

void
bureau_update ()
{
    if (event_update(this.entityOnCreate))
    {
        // Une personne vient d'arriver

        if (bb_queue_get_length(this.entities) < this.max_capacity)
        {
            // Ne pas dépasser la limite autorisée de personnes dans le bureau de vote
            switch (fork())
            {
                case -1: printf("Erreur fork\n"); break;
                case 0:
                {
                    // Fils
                    Entity *e = entity_new();
                    bb_queue_add(this.entities, e);
                    printf("Entity %ld is alive\n", e->id);
                    entity_main(e);
                    printf("Entity %ld died\n",  e->id);
                    exit(0);
                }
                break;

                default: // Père
                    // Rien à faire, continuer d'actualiser le bureau
                break;
            }

            printf("%d = Welcome\n", this.now);
        }

        else
        {
            printf("Bureau de vote : Trop d'entités dans le bureau (%d)\n", this.max_capacity);
        }
    }
}

