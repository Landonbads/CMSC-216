/* Name: Landon Badstibner
 * Date: 04/11/2023
 * Terpconnect: landonb
 * UID: 119011416
 * Section: 0203
 *
 * Project 07 - A header file containing the definition for the
 * representation of a graph via adjacency list implementation,
 * with string vertex names & weighted, directed, eges
 *
 * I pledge on my honor that I have not given or received
 * any unauthorized assistance on this assignment
 */

#if !defined(STRING_GRAPH_DATASTRUCTURE_H)
#define STRING_GRAPH_DATASTRUCTURE_H

/* edge struct to represent edge in the graph */
typedef struct edge
{
    /* destination vertex that the edge points to */
    struct vertex *destination_vertex;
    /* next edge, another outgoing edge from source vertex */
    struct edge *next_edge;
    /* weight of the edge */
    int weight;
} Edge;

/* vertex struct to represent a vertex in the graph */
typedef struct vertex
{
    /* name of vertex */
    char *name;
    /* pointer to the first edge of the vertex */
    Edge *edge_list;
} Vertex;

/* graph struct to represent entire graph */
typedef struct graph
{
    /* number of verticees in the graph */
    int num_vertices;
    /* list for adjacency list representation */
    Vertex **vertex_list;
} String_graph;
#endif