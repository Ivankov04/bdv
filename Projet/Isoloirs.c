#include "Isoloirs.h"
#include <stdlib.h>

Isoloirs *
isoloirs_new (void)
{
	Isoloirs *this;

	if ((this = malloc(sizeof(Isoloirs))) == NULL)
		return NULL;

	isoloirs_init(this);

	return this;
}

void
isoloirs_init (Isoloirs *this)
{
	for (int i = 0; i < ISOLOIRS_NB_CABINES; i++)
	{
		this->isoloirs[i] = lieu_new(ISOLOIR, 7, 10, 1, NULL);
	}
}

void
isoloirs_free (Isoloirs *isoloirs)
{
	if (isoloirs != NULL)
	{
		free (isoloirs);
	}
}
