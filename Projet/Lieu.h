#pragma once

// ---------- Includes ------------
#include "../BbQueue/BbQueue.h"

// ---------- Defines -------------
typedef enum {

	ENTREE_SORTIE,
	SECRETARIAT,
	BUREAU_PRESIDENT,
	ISOLOIRS,
	ISOLOIR,
	ASSESSEUR,
	ASCENSEUR,
	ETAGE_ASCENSEUR,

} LieuType;


// ------ Class declaration -------
typedef struct
{
	LieuType type;

	// Durée passée par une entity dans le Lieu
	int duree_min;
	int duree_max;

	// Maximum d'entité
	int max_capacity;
	BbQueue *entities;

	// Autre implémentation
	void *user_data;

}	Lieu;


// --------- Constructors ---------

Lieu *
lieu_new (LieuType type, int duree_min, int duree_max, int max_capacity, void *data);


// ----------- Methods ------------

void
lieu_init (Lieu *this, LieuType type, int duree_min, int duree_max, int max_capacity, void *data);


// --------- Destructors ----------

void
lieu_free (Lieu *lieu);


