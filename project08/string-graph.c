/* Name: Landon Badstibner
 * Date: 04/11/2023
 * Terpconnect: landonb
 * UID: 119011416
 * Section: 0203
 *
 * Project 08 - 5 extra functions to project 7 to remove vertices/edges
 * and resolve memory management
 *
 * I pledge on my honor that I have not given or received
 * any unauthorized assistance on this assignment
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string-graph.h"

/* helper function prototype(s) */
static Vertex *get_vertex(const String_graph *const graph, const char name[]);

/**
 * graph_init function to initialize a specified graph
 * @param graph - pointer to the graph to be used
 */
void graph_init(String_graph *const graph)
{
    String_graph *new_graph = NULL;
    /* check if graph parameter is NULL */
    if (graph != NULL)
    {
        /* allocate memory for new graph */
        new_graph = malloc(sizeof(String_graph));

        /* set the # of vertices in the graph to 0 */
        new_graph->num_vertices = 0;
        /* allocate memory for the graph vertex list */
        new_graph->vertex_list = malloc(sizeof(Vertex *));

        /* set graph parameter to new graph */
        *graph = *new_graph;

        free(new_graph);
    }
}

/**
 * add_vertex_to_graph function to add a specified vertex to the graph
 * @param graph - pointer to the graph to be used
 * @param new_vertex - name of the new vertex to be added
 * @return 1 if vertex succesfully added to graph, 0 otherwise
 */
short add_vertex_to_graph(String_graph *const graph, const char new_vertex[])
{
    /* declare useful variables */
    char *new_name = NULL;
    int i;
    Vertex *new_vertex_ptr = NULL;

    /* check if parameters are NULL */
    if (graph == NULL || new_vertex == NULL)
        return 0;

    /* check if new_vertex name matches a vertex  name already in the graph */
    for (i = 0; i < graph->num_vertices; i++)
    {
        if (strcmp(new_vertex, graph->vertex_list[i]->name) == 0)
            /* return 0 if vertex name already exists in the graph */
            return 0;
    }

    /* dynamically allocate right amount of memory for the new name */
    new_name = malloc(strlen(new_vertex) + 1);
    /* increase num_vertices variable of the graph by 1 */
    graph->num_vertices += 1;

    /* copy new vertex name into new_name, dynamically allocated string */
    strcpy(new_name, new_vertex);

    /* allocate memory for the vertex */
    new_vertex_ptr = malloc(sizeof(Vertex));
    /* set the new vertex name to the new name */
    new_vertex_ptr->name = new_name;
    /* set edge list of new vertex to NULL */
    new_vertex_ptr->edge_list = NULL;

    /* reallocate the memory for the graph to include enough for new vertex */
    graph->vertex_list = realloc(graph->vertex_list,
                                 sizeof(Vertex *) * graph->num_vertices);
    /* add new vertex to vertex_list */
    graph->vertex_list[graph->num_vertices - 1] = new_vertex_ptr;

    /* return 1 if successfully added */
    return 1;
}

/**
 * vertex_count function to count # of vertices in a graph
 * @param graph - pointer to the graph to be used
 * @return # of vertices in the graph
 */
short vertex_count(const String_graph *const graph)
{
    /* check if graph is NULL */
    if (graph != NULL)
        /* return number of vertices in the graph (could be zero) */
        return graph->num_vertices;

    /* otherwise, return 0 if graph is NULL */
    return 0;
}

/**
 * isa_vertex function to check if specified vertex is in a graph
 * @param graph - pointer to the graph to be used
 * @param name - name of vertex to check
 * @return 0 if vertex not found or 1 if vertex is in the graph
 */
short isa_vertex(const String_graph *const graph, const char name[])
{
    int i;
    /* check if parameters are NULL */
    if (graph != NULL && name != NULL)
    {
        /* iterate through graph */
        for (i = 0; i < graph->num_vertices; i++)
        {
            /* compare vertex name at ith element with parameter name */
            if (strcmp(graph->vertex_list[i]->name, name) == 0)
                /* return 1 if vertex in graph with specified name exists */
                return 1;
        }
    }
    /* return 0 if vertex not found */
    return 0;
}

/**
 * get_vertex_list function to obtain array of vertex names in
 * lexicographic order
 * @param graph - pointer to the graph to be used
 * @return array with n + 1 elements, n being # of vertices in graph
 */
char **get_vertex_list(const String_graph *const graph)
{
    /* declare necessary variables for function */
    char **arr = NULL;
    int i;
    int j;
    char *temp = NULL;

    /* if graph equals NULL, return NULL */
    if (graph == NULL)
        return NULL;

    /* allocate memory for the list of strings, corresponding to the
    # of vertices in the graph. Also add extra sizeof() for last NULL entry */
    arr = malloc(graph->num_vertices * sizeof(char *) + sizeof(char *));

    /* iterate through the graph, allocating memory for each element and
    copying vertex name into copied array */
    for (i = 0; i < graph->num_vertices; i++)
    {
        char *name = malloc(strlen(graph->vertex_list[i]->name) + 1);
        strcpy(name, graph->vertex_list[i]->name);
        arr[i] = name;
    }

    /* iterate through the graph and use bubble sort algorithm to sort the
    strings into dictionary order as required*/
    for (i = 0; i < graph->num_vertices - 1; i++)
    {
        for (j = 0; j < graph->num_vertices - i - 1; j++)
        {
            /* if next element is "bigger" than previous element, switch */
            if (strcmp(arr[j], arr[j + 1]) > 0)
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    /* set last element of array to NULL and return the array*/
    arr[graph->num_vertices] = NULL;
    return arr;
}

/**
 * create_graph_edge function to add a specified edge to a graph
 * @param graph - pointer to the graph to be used
 * @param source - name of the source vertex of the edge to be added
 * @param dest - name of the destination vertex of the edge to be added
 * @param weight - weight of the edge to be added
 * @return 1 if the edge was successfully added
 */
short create_graph_edge(String_graph *const graph, const char source[],
                        const char dest[], int weight)

{
    /* declare important variables needed to perform function*/
    Vertex *source_vertex;
    Edge *edge;
    Vertex *dest_vertex;

    /* ensure weight is non-negative */
    if (weight < 0)
        return 0;
    /* check if source vertex is a vertex in the graph, if not add it */
    if (!(isa_vertex(graph, source)))
        add_vertex_to_graph(graph, source);
    /* check if destination vertex is a vertex in the graph, if not add it */
    if (!(isa_vertex(graph, dest)))
        add_vertex_to_graph(graph, dest);
    /* find source vertex */
    source_vertex = get_vertex(graph, source);
    if (source_vertex == NULL)
        return 0;

    /* iterate over the edges for the source vertex while edge is not NULL*/
    edge = source_vertex->edge_list;
    while (edge)
    {
        if (strcmp(edge->destination_vertex->name, dest) == 0)
        {
            /* an edge from source to dest already exists, update its weight */
            edge->weight = weight;
            return 1;
        }
        /* iterate to next edge */
        edge = edge->next_edge;
    }

    /* no edge from source to dest exists, create a new edge */
    dest_vertex = get_vertex(graph, dest);

    if (dest_vertex == NULL)
        return 0;

    /* allocate memory for edge */
    edge = malloc(sizeof(Edge));
    /* set edge weight to specified weight */
    edge->weight = weight;
    /* set edge destination vertex to specified vertex */
    edge->destination_vertex = dest_vertex;
    /* set edges next edge to the front of the edge list for source vertex */
    edge->next_edge = source_vertex->edge_list;
    /* oficially make the edge the front of the list (first
        node the source vertex points too) */
    source_vertex->edge_list = edge;

    /* return 1 if edge successfully added */
    return 1;
}

/**
 * get_graph_edge_weight function to determine the weight of a specific edge
 * @param graph - pointer to the graph to be used
 * @param source - name of the source vertex
 * @param dest - name of the destination vertex
 * @return the weight of a specific edge
 */
short get_graph_edge_weight(const String_graph *const graph,
                            const char source[], const char dest[])
{
    /* if the parameters are not null and vertices exist in graph, continue */
    if (graph != NULL && source != NULL && dest != NULL &&
        isa_vertex(graph, source) != 0 && isa_vertex(graph, dest) != 0)
    {
        /* set source vertex to vertex in graph with specified name */
        Vertex *source_vertex = get_vertex(graph, source);

        /*iterate over edges to return edge weight if it exists */
        Edge *edge = source_vertex->edge_list;
        while (edge)
        {
            if (strcmp(edge->destination_vertex->name, dest) == 0)
            {
                return edge->weight;
            }
            edge = edge->next_edge;
        }
    }
    /* if either any parameter is null or vertices do not exist in graph
    then return -1 */
    return -1;
}

/**
 * neighbor_count function to count the # of neighbors a specific vertex has
 * @param graph - pointer to the graph to be used
 * @param vertex - name of the vertex to find neighbors for
 * @return number of neighbors a specific vertex has
 */
short neighbor_count(const String_graph *const graph, const char vertex[])
{
    /* declare and initialize counter variable to track neighbors*/
    short counter = 0;
    /* declare vertex required to iterate through */
    Vertex *parameter_vertex;
    /* declare Edge variable to help with iteration */
    Edge *edge;

    /* check if any of the parameters are NULL, return -1 if so */
    if (graph == NULL || vertex == NULL || isa_vertex(graph, vertex) == 0)
        return -1;

    /* utilize helper function to find vertex with specified name */
    parameter_vertex = get_vertex(graph, vertex);

    /* iterate over edges to count # of outgoing edges */
    edge = parameter_vertex->edge_list;
    while (edge)
    {
        counter++;
        edge = edge->next_edge;
    }
    /* finally, return # of neighbors, 0 if no neighbors */
    return counter;
}

/**
 * get_vertex helper function to return vertex in a graph with parameter name
 * @param graph - pointer to the graph to be used
 * @param name - name of the vertex to find
 * @return vertex if vertex is in the graph, NULL otherwise
 */
Vertex *get_vertex(const String_graph *const graph, const char name[])
{
    int i;

    /* iterate through the graph to check if vertex exists with parameter name.
    If so, return a pointer to that vertex */
    for (i = 0; i < graph->num_vertices; i++)
    {
        if (strcmp(graph->vertex_list[i]->name, name) == 0)
            return graph->vertex_list[i];
    }

    /* return NULL if vertex doesn't exist */
    return NULL;
}

void free_vertex_name_list(char **const names)
{
    int i;
    if (names != NULL)
    {
        for (i = 0; names[i] != NULL; i++)
            free(names[i]);

        free(names);
    }
}

/* return array of strings to neighbors of specific vertex*/
char **get_neighbor_names(const String_graph *const graph, const char vertex[])
{
    int i;
    int j;
    char *temp = NULL, *new_string = NULL;
    int counter = 0;
    Vertex *param_vertex = NULL;
    Edge *ph_edge = NULL;

    /* allocate memory for new array corresponding to # of
    neighbors and ending NULL entry */
    char **new_arr = malloc(sizeof(char *) *
                            (neighbor_count(graph, vertex) + 1));

    if (graph != NULL && get_vertex(graph, vertex) != NULL)
    {
        param_vertex = get_vertex(graph, vertex);
        ph_edge = param_vertex->edge_list;

        while (ph_edge)
        {
            char *new_name = malloc(strlen(
                                        ph_edge->destination_vertex->name) +
                                    1);
            strcpy(new_name, ph_edge->destination_vertex->name);
            new_arr[counter] = new_name;

            ph_edge = ph_edge->next_edge;
            counter++;
        }

        /* sort array in lexicographic order using bubble sort algorithm*/
        for (i = 0; i < counter; i++)
        {
            for (j = i + 1; j < counter; j++)
            {
                if (strcmp(new_arr[i], new_arr[j]) > 0)
                {
                    temp = malloc(strlen(new_arr[i]) + 1);
                    strcpy(temp, new_arr[i]);
                    free(new_arr[i]);
                    new_string = new_arr[j];
                    new_arr[i] = new_string;
                    new_arr[j] = temp;

                    /*temp = new_arr[i];
                    new_arr[i] = new_arr[j];
                    new_arr[j] = temp;*/
                }
            }
        }

        /* set last entry to NULL, which had memory
        allocated in the beginning */
        new_arr[neighbor_count(graph, vertex)] = NULL;

        return new_arr;
    }

    return NULL;
}

/* remove edge from specified graph with source and dest vertices */
int remove_graph_edge(String_graph *const graph, const char source[],
                      const char dest[])
{
    int i = 0;
    Edge *edge = NULL;
    Edge *prev_edge = NULL;
    Vertex *src_vertex = NULL;
    int contains = 0;

    /* check if source and dest vertices exist in the graph */
    if (!get_vertex(graph, source) || !get_vertex(graph, dest))
        return 0;

    /* set vars needed for subsequent while loop */
    src_vertex = get_vertex(graph, source);
    edge = src_vertex->edge_list;

    /* checks if the source vertex has an edge going to destination vertex */
    while (edge)
    {
        if (strcmp(edge->destination_vertex->name, dest) == 0)
        {
            contains = 1;
        }
        edge = edge->next_edge;
    }
    if (contains == 0)
        return 0;

    /* reset edge and initialize prev_edge */
    edge = src_vertex->edge_list;

    /* loop through edge list of vertex to find edge and remove it */
    for (i = 0; edge; i++)
    {
        if (strcmp(edge->destination_vertex->name, dest) == 0)
        {
            /* if i is zero it must be first iteration, therefore
             this is the first edge in edge list */
            if (i == 0)
            {
                src_vertex->edge_list = edge->next_edge;
                edge->destination_vertex = NULL;
            }
            /* otherwise must be an edge before it*/
            else
            {
                /* set prev_edge's next edge to edge's next edge*/
                prev_edge->next_edge = edge->next_edge;
                /* set edge's destination vertex to NULL */
                edge->destination_vertex = NULL;
            }
            /* free the memory for the edge */
            free(edge);
            return 1;
        }
        prev_edge = edge;
        edge = edge->next_edge;
    }
    return 0;
}

/* remove specific vertex from specific graph with vertex name*/
int remove_vertex_from_graph(String_graph *const graph, const char vertex[])
{
    Vertex *pvertex = NULL;
    Edge *curr = NULL, *prev = NULL;
    int i;
    int j;
    if (!get_vertex(graph, vertex))
        return 0;

    pvertex = get_vertex(graph, vertex);
    curr = pvertex->edge_list;

    /* loop through outgoing edges to remove them & free memory */
    while (curr)
    {
        prev = curr;
        curr = curr->next_edge;
        free(prev);
    }

    /* remove all incoming edges and free memory */
    /*for (i = 0; i < graph->num_vertices; i++)
    {
        pvertex = graph->vertex_list[i];
        edge = pvertex->edge_list;
        while (edge)
        {
            if (strcmp(edge->destination_vertex->name, vertex) == 0)
            {
                remove_graph_edge(graph, pvertex->name, vertex);
                break;
            }

            edge = edge->next_edge;
        }
    }*/

    /* reassign pvertex */
    pvertex = get_vertex(graph, vertex);

    for (i = 0; i < graph->num_vertices; i++)
    {
        if (strcmp(graph->vertex_list[i]->name, vertex) == 0)
        {

            /* reorder vertex_list if there is more than 1 vertex
            in the graph */
            if (graph->num_vertices > 1)
            {
                for (j = i; j < graph->num_vertices - 1; j++)
                    graph->vertex_list[j] = graph->vertex_list[j + 1];
            }
            /* if only 1 vertex in the graph, set the vertex_list to NULL*/
            else
            {
                graph->vertex_list = NULL;
            }
        }
    }
    free(pvertex->name);
    free(pvertex);
    graph->num_vertices -= 1;

    graph->vertex_list = realloc(graph->vertex_list, graph->num_vertices * (sizeof(Vertex *)));
    return 1;
}

/* remove all vertices & edges in the graph & free all memory */
void graph_delete(String_graph *const graph)
{
    /* free memory for each vertex w/o helper function b/c my code is trash */
    int i = 0;
    Edge *curr_edge = NULL;
    Vertex *curr_vertex = NULL;
    Edge *temp = NULL;

    /* loop through vertex list */
    for (i = 0; i < graph->num_vertices; i++)
    {

        curr_vertex = graph->vertex_list[i];
        curr_edge = curr_vertex->edge_list;

        /* while the edge is not null execute this code */
        while (curr_edge)
        {
            /* set temp to current edge and set current edge to next one */
            temp = curr_edge;
            curr_edge = temp->next_edge;

            /* free the edge */
            free(temp);
        }

        /* free the vertex name and the vertex itself. then free the edge */
        free(curr_vertex->name);
        free(curr_edge);
        free(curr_vertex);
    }

    /* free the entire graph */
    free(graph->vertex_list);
}