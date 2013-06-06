#pragma once

// ---------- Includes ------------
#include "./Lieu.h"

// ---------- Defines -------------


// ------ Class declaration -------
typedef struct _Entree
{
    // Entree hérite de Lieu
    Lieu *father;





}	Entree;



// --------- Constructors ---------

Entree *
entree_new (Lieu *lieu);


// ----------- Methods ------------
void
entree_init (Entree *this, Lieu *lieu);

void
entree_update (Entree *entree);



// --------- Destructors ----------

void
entree_free (Entree *entree);


