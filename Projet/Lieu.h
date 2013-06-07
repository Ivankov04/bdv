#pragma once

// ---------- Includes ------------
#include "../BbQueue/BbQueue.h"
#include "./Entity.h"

// ---------- Defines -------------
#define LIEU_METHODS(e) (void *(*)(Lieu *)) e##_new, (void (*)(void *)) e##_update

// ------ Class declaration -------

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


typedef struct
{
	LieuType type;

	// Durée passée par une entity dans le Lieu
	int duree_min;
	int duree_max;

	// Maximum d'entités
	int max_capacity;
	BbQueue *entities;

	// Etage du lieu
	int etage;

	// Autres implémentations
	void *user_data;
	void (*update)(void *);

	// Informations affichage
	char *nom;

}	Lieu;


// --------- Constructors ---------

Lieu *lieu_new (LieuType type, int etage, int duree_min, int duree_max, int max_capacity, void *(*constructor)(Lieu *), void (*update)(void *arg));

// ----------- Methods ------------

void lieu_init          (Lieu *this, LieuType type, int etage, int duree_min, int duree_max, int max_capacity, void *(*constructor)(Lieu *), void (*update)(void *arg));
void lieu_add_entity    (Lieu *this, Entity *entity);
void lieu_update        (Lieu *this);
bool lieu_plein         (Lieu *this);

// --------- Destructors ----------

void lieu_free (Lieu *lieu);


