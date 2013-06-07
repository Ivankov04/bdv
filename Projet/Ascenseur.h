#pragma once

// ---------- Includes ------------
#include "./Lieu.h"


// ---------- Defines -------------
#define LVL0_LVL1 2
#define LVL1_LVL2 4
#define LVL2_LVL0 6

// ------ Class declaration -------
typedef struct _Ascenseur
{
	Lieu *father;

	Lieu *level[3];
	Lieu *cur;
	Lieu *dest;

	BbQueue *entities_inside;

}	Ascenseur;



// --------- Constructors ---------

Ascenseur *
ascenseur_new (Lieu *father);

void
ascenseur_update (Ascenseur *this);


// ----------- Methods ------------
void
ascenseur_init (Ascenseur *ascenseur, Lieu *father);



// --------- Destructors ----------

void
ascenseur_free (Ascenseur *ascenseur);


