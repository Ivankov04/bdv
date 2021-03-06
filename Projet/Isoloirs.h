#pragma once

// ---------- Includes ------------
#include "./Lieu.h"

// ---------- Defines -------------
#define ISOLOIRS_NB_CABINES 4

// ------ Class declaration -------
typedef struct _Isoloirs
{
	Lieu *isoloirs[ISOLOIRS_NB_CABINES];
	Lieu *father;

}	Isoloirs;



// --------- Constructors ---------

Isoloirs *
isoloirs_new (Lieu *lieu);


// ----------- Methods ------------
void
isoloirs_init (Isoloirs *isoloirs, Lieu *lieu);

void
isoloirs_update (Isoloirs *isoloirs);


// --------- Destructors ----------

void
isoloirs_free (Isoloirs *isoloirs);
