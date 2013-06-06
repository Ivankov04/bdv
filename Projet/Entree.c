#include "Entree.h"
#include <stdlib.h>
#include <stdio.h>

Entree *
entree_new (Lieu *lieu)
{
	Entree *this;

	if ((this = malloc(sizeof(Entree))) == NULL)
		return NULL;

	entree_init(this, lieu);

	return this;
}

void
entree_init (Entree *this, Lieu *lieu)
{
    this->father = lieu;
}

void
entree_update (Entree *this)
{

}

void
entree_free (Entree *entree)
{
	if (entree != NULL)
	{
		free (entree);
	}
}
