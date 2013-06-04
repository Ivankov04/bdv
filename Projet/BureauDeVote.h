#pragma once

// ---------- Includes ------------
#include "../Graph/Graph.h"
#include "../Event/Event.h"
#include "./Lieu.h"
#include "./Ascenseur.h"
#include "./Isoloirs.h"
#include "./Entity.h"

// ---------- Defines -------------
#define MAX_ENTITIES_IN_BDV 11

// ------ Class declaration -------
typedef struct _BureauDeVote
{
    int max_capacity;

    BbQueue *entities;

	Graph *graph;
	Event *entityOnCreate;

	clock_t start;
	int now;

	bool alive;

}	BureauDeVote;

unsigned long int entity_generated;

// --------- Constructors ---------


// ----------- Methods ------------

void
bureau_init (int max_entities);

void
bureau_update ();

void
bureau_main ();


// --------- Destructors ----------
