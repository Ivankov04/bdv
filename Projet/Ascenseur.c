#include "Ascenseur.h"
#include <stdlib.h>

Ascenseur *
ascenseur_new (void)
{
	Ascenseur *this;

	if ((this = malloc(sizeof(Ascenseur))) == NULL)
		return NULL;

	ascenseur_init(this);

	return this;
}

void
ascenseur_init (Ascenseur *this)
{
	this->lv1 = lieu_new(ETAGE_ASCENSEUR, 3, 3, 2, NULL);
	this->lv2 = lieu_new(ETAGE_ASCENSEUR, 3, 3, 2, NULL);
	this->lv3 = lieu_new(ETAGE_ASCENSEUR, 3, 3, 2, NULL);

	this->cur = this->lv1;
}

void
ascenseur_free (Ascenseur *ascenseur)
{
	if (ascenseur != NULL)
	{
		free (ascenseur);
	}
}
