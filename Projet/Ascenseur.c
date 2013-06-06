#include "Ascenseur.h"
#include <stdlib.h>

Ascenseur *
ascenseur_new (Lieu *father)
{
	Ascenseur *this;

	if ((this = malloc(sizeof(Ascenseur))) == NULL)
		return NULL;

	ascenseur_init(this, father);

	return this;
}

void
ascenseur_init (Ascenseur *this, Lieu *father)
{
	this->lv1 = lieu_new(ETAGE_ASCENSEUR, 3, 3, 2, NULL, NULL);
	this->lv2 = lieu_new(ETAGE_ASCENSEUR, 3, 3, 2, NULL, NULL);
	this->lv3 = lieu_new(ETAGE_ASCENSEUR, 3, 3, 2, NULL, NULL);

	this->cur = this->lv1;

	this->father = father;
}

void
ascenseur_update (Ascenseur *this)
{

}

void
ascenseur_free (Ascenseur *ascenseur)
{
	if (ascenseur != NULL)
	{
		free (ascenseur);
	}
}
