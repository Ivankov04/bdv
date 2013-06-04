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

}	Ascenseur;



// --------- Constructors ---------

Ascenseur *
ascenseur_new (void);


// ----------- Methods ------------
void
ascenseur_init (Ascenseur *ascenseur);



// --------- Destructors ----------

void
ascenseur_free (Ascenseur *ascenseur);


