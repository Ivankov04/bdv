#include "Lieu.h"
#include <stdlib.h>
#include <stdio.h>

Lieu *
lieu_new (LieuType type, int duree_min, int duree_max, int max_capacity, void *data)
{
	Lieu *this;

	if ((this = calloc(1, sizeof(Lieu))) == NULL)
		return NULL;

	lieu_init(this, type, duree_min, duree_max, max_capacity, data);

	return this;
}

void
lieu_init (Lieu *this, LieuType type, int duree_min, int duree_max, int max_capacity, void *data)
{
	this->type = type;
	this->duree_min = duree_min;
	this->duree_max = duree_max;
	this->max_capacity = max_capacity;
	this->entities = bb_queue_new();
	this->user_data = data;
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
lieu_free (Lieu *lieu)
{
	if (lieu != NULL)
	{
		free (lieu);
	}
}
