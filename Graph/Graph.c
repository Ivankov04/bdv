/**
 *	@author		:	Spl3en (Moreau Cyril) <spl3en.contact@gmail.com>
 *	@file		:	Graph.c
 *
 *	Furthermore informations in Graph.h
*/

#include "Graph.h"

/* Constructeurs */
// Graph
Graph *
graph_new ()
{
	Graph *p = (Graph *) malloc (sizeof(Graph));

	if (p == NULL)
		return NULL;

    p->vertices = bb_queue_new();

	return p;
}

// GraphArc
GraphArc *
graph_arc_new (GraphVertex *from, GraphVertex *to)
{
    GraphArc *a = (GraphArc *) malloc (sizeof(GraphArc));

    if (a == NULL)
        return NULL;

    a->from = from;
    a->to = to;

    a->user_data  = NULL;
    a->_impl_data = NULL;

    bb_queue_add(a->from->arcs, a);

    return a;
}

// GraphVertex
GraphVertex *
graph_vertex_new (void)
{
    GraphVertex *v = (GraphVertex *) malloc (sizeof(GraphVertex));

    if (v == NULL)
        return NULL;

    v->arcs = bb_queue_new();

    v->user_data  = NULL;
    v->_impl_data = NULL;

    return v;
}

/* Methodes */
// GraphArc
GraphArc *
graph_add_arc (Graph *g, GraphVertex *from, GraphVertex *to)
{
    GraphArc *a = NULL;

    a = graph_arc_new(from, to);

    if (!bb_queue_exists(g->vertices, from))
        bb_queue_add(g->vertices, from);

    if (!bb_queue_exists(g->vertices, to))
        bb_queue_add(g->vertices, to);

    return a;
}

GraphArc *
graph_vertex_get_arc (GraphVertex *from, GraphVertex *to)
{
    GraphArc *a = NULL;

    foreach_bbqueue_item (from->arcs, a)
    {
        if (a->to == to)
            return a;
    }

    return NULL;
}

void
graph_debug (Graph *g)
{
    int loop_counter = 0;

    foreach_bbqueue_item(g->vertices, GraphVertex *vertex)
    {
        printf("- Arcs du vertex %c : \n", 'A' + loop_counter++);

        foreach_bbqueue_item(vertex->arcs, GraphArc *arc)
        {
            printf("(0x%x) -> 0x%x\n", (int)arc->from, (int)arc->to);
        }

        printf("\n");
    }
}

// Graph
void
graph_unref (Graph *p)
{
	if (p != NULL)
	{
		free(p);
	}
}

