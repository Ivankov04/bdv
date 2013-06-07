#pragma once

// ---------- Includes ------------
#include "../Graph/Graph.h"
#include "../Event/Event.h"
#include "./Lieu.h"
#include "./Ascenseur.h"
#include "./Isoloirs.h"
#include "./Entity.h"
#include "./Entree.h"
#include "./Secretariat.h"

// ---------- Defines -------------
#define MAX_ENTITIES_IN_BDV 1
#define PATH_SIZE           9

// ------ Class declaration -------
typedef struct _BureauDeVote
{
    int max_capacity;

    BbQueue *entities;
	Event *entity_on_create;

	clock_t start;
	int now;

	bool alive;

	// Lieux
	Lieu *entree,
		 *secretariat,
		 *bureau,
		 *isoloirs,
		 *assesseur,
		 *ascenseur;

    Lieu **chemin;

}	BureauDeVote;

unsigned long int entity_generated;

// --------- Constructors ---------


// ----------- Methods ------------

void
bdv_init (int max_entities);

void
bdv_update ();

void
bdv_main ();

void
bdv_give_path (Entity *entity);

clock_t
bdv_get_ticks ();

// --------- Destructors ----------
