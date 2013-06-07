#include "Isoloirs.h"
#include <stdlib.h>

Isoloirs *
isoloirs_new (Lieu *lieu)
{
	Isoloirs *this;

	if ((this = malloc(sizeof(Isoloirs))) == NULL)
		return NULL;

	isoloirs_init(this, lieu);

	return this;
}

void
isoloirs_init (Isoloirs *this, Lieu *lieu)
{
	for (int i = 0; i < ISOLOIRS_NB_CABINES; i++)
	{
		this->isoloirs[i] = lieu_new(ISOLOIR, lieu->etage, 7, 10, 1, NULL, NULL);
	}

	this->father = lieu;
}

void
isoloirs_update (Isoloirs *this)
{

}

void
isoloirs_free (Isoloirs *isoloirs)
{
	if (isoloirs != NULL)
	{
		free (isoloirs);
	}
}
