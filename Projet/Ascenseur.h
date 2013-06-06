#pragma once

// ---------- Includes ------------
#include "./Lieu.h"


// ---------- Defines -------------


// ------ Class declaration -------
typedef struct _Ascenseur
{
	Lieu *lv1;
	Lieu *lv2;
	Lieu *lv3;
	Lieu *cur;
	Lieu *father;

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


