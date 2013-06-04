/**
 *  @author		:	Spl3en (Moreau Cyril) <spl3en.contact@gmail.com>
 *  @file		:	Graph.h
 *  @version	:	1.0
 *  @date		:	2011-03-12-23.40
*/

#ifndef Graph_H_INCLUDED
#define Graph_H_INCLUDED

/* Includes */
#include <stdlib.h>
#include <stdio.h>

#include "../BbQueue/BbQueue.h"

/*
    Note pour les structures suivantes :

        _impl_data est destiné à recueillir des informations liées à l'implémentation
        de différents algorithmes de la théorie des graphes ; Il n'est pas conseillé
        d'y toucher lors d'une utilisation de la librairie. user_data est là pour ça.
*/

typedef
struct _Vertex
{
    /* Chaque Vertex peut être relié de [0..*] Arcs */
    BbQueue *arcs;

    void *_impl_data;
    void *user_data;

}   GraphVertex;

typedef
struct _Arc
{
    /* Un Arc est situé entre deux vertices */
    GraphVertex *from,
                *to;

    void *_impl_data;
    void *user_data;

}   GraphArc;

typedef
struct _Graph
{
    /* Un Graph est un ensemble de Vertices */
    BbQueue *vertices;

}	Graph;


	/**=================
		@Constructors
	===================*/

Graph *
graph_new 				(void);

GraphArc *
graph_arc_new           (GraphVertex *from, GraphVertex *to);

GraphVertex *
graph_vertex_new        (void);


	/**=================
		  @Methods
	===================*/

GraphArc *
graph_add_arc           (Graph *g, GraphVertex *from, GraphVertex *to);

void
graph_debug             (Graph *g);

GraphArc *
graph_vertex_get_arc    (GraphVertex *from, GraphVertex *to);

	/**=================
		@Destructors
	===================*/

void
graph_unref 			(Graph *p);

#endif
