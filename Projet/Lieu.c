#include "Lieu.h"
#include <stdlib.h>
#include <stdio.h>

char *lieux_nom[] = {"Entree/Sortie", "Secretariat", "Bureau du président", "Isoloirs", "Un Isoloir", "Assesseur", "Ascenseur", "Etage ascenseur"};

Lieu *
lieu_new (LieuType type, int duree_min, int duree_max, int max_capacity, void *(*constructor)(Lieu *), void (*update)(void *arg))
{
	Lieu *this;

	if ((this = calloc(1, sizeof(Lieu))) == NULL)
		return NULL;

	lieu_init(this, type, duree_min, duree_max, max_capacity, constructor, update);

	return this;
}

void lieu_init (Lieu *this, LieuType type, int duree_min, int duree_max, int max_capacity, void *(*constructor)(Lieu *), void (*update)(void *arg))
{
	this->type = type;
	this->duree_min = duree_min;
	this->duree_max = duree_max;
	this->max_capacity = max_capacity;
	this->entities = bb_queue_new();
	this->update = update;

	if (constructor != NULL)
        this->user_data = constructor(this);

    this->nom = lieux_nom[(int)type];
}

void
lieu_debug (Lieu *lieu)
{
	printf("Lieu DEBUG\n"
		"Type : %d\n"
		"Duree min-max : %d - %d\n"
		"Max  capacity :  %d\n",
			lieu->type,
			lieu->duree_min, lieu->duree_max,
			lieu->max_capacity
	);
}

void
lieu_add_entity (Lieu *this, Entity *entity)
{
    bb_queue_add(this->entities, entity);
}

void
lieu_update (Lieu *this)
{
    if (this->update != NULL)
        this->update(this->user_data);
}

void
lieu_free (Lieu *lieu)
{
	if (lieu != NULL)
	{
		free (lieu);
	}
}
