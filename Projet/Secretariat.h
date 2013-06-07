#pragma once

// ---------- Includes ------------
#include "./Lieu.h"

// ---------- Defines -------------


// ------ Class declaration -------
typedef struct _Secretariat
{
    Lieu *father;



}	Secretariat;

// --------- Constructors ---------

Secretariat *
secretariat_new (Lieu *father);


// ----------- Methods ------------
void
secretariat_init (Secretariat *secretariat, Lieu *father);

void
secretariat_update (Secretariat *this);



// --------- Destructors ----------

void
secretariat_free (Secretariat *secretariat);


