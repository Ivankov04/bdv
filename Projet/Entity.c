#include "Entity.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

static unsigned long long int id = 0;

static void entity_update (Entity *this);
static void entity_main (Entity *this);

/* Ces fonctions ne sont gérées que par le processus de l'entitée */
static void entity_update (Entity *this)
{
    if (this->wakeup != NULL)
    {
        if (event_update(this->wakeup))
        {
            if (this->walking == FALSE)
            {
                applog("Entité", "%lu - marche vers la prochaine destination", this->id);
                this->walking = TRUE;
                event_restart_now(&this->wakeup, 3000, 3000); // 3s pour aller au prochain point
            }

            else
            {
                event_free(this->wakeup);
                this->id_path++;
                this->ready   = TRUE;
                this->wakeup  = NULL;
                this->walking = FALSE;
            }
        }
    }
}

static void entity_main (Entity *this)
{
    entity_lock(this);

    while (this->alive)
    {
        entity_unlock(this);

        usleep(1000 * 100);

        entity_lock(this);
        entity_update(this);
    }

    entity_unlock(this);
}

/* Fonctions publiques */
void entity_lock (Entity *this)
{
    pthread_mutex_lock(&this->mutex);
}

void entity_unlock (Entity *this)
{
    pthread_mutex_unlock(&this->mutex);
}

Entity *entity_new (void)
{
	Entity *this;

	if ((this = calloc(1, sizeof(Entity))) == NULL)
		return NULL;

	entity_init(this);

	return this;
}

bool entity_is_dead (Entity *this)
{
    return (this->alive == FALSE && this->start > 0);
}

void entity_init (Entity *this)
{
    this->thread = thread_new((void(*)(void *))entity_main, this);
    memset(&this->mutex, 0, sizeof(pthread_mutex_t));
}

void entity_make_alive (Entity *this)
{
    this->start   = event_get_now();
    this->alive   = TRUE;
    this->ready   = TRUE;
    this->id      = id;
    this->id_path = 0;

    thread_create(this->thread);
    applog("Entité", "%llu - crée", id++);
}

void entity_free (Entity *e)
{
	if (e != NULL)
	{
	    event_free(e->wakeup);
        thread_exit(e->thread);
		free (e);
	}
}
