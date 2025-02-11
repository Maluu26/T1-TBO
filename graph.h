#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

typedef struct graph graph;

/**
 * Creates a graph
 * @param size graph's size
 * @return graph pointer
 */
graph * create_graph(int size);

/**
 * Inserts a new edge or modifies an already existing one
 * @param g graph to add the edge
 * @param src source node
 * @param dst destiny node
 * @param w edge's weight
 */
void insert_edge(graph * g, int src, int dst, float w);

/**
 * Turns the value of the edge to 0
 * @param g graph to remove the edge
 * @param src source node
 * @param dst destiny node
 */
void remove_edge(graph * g, int src, int dst);

/**
 * Gets the value of an edge if it exists
 * @param g graph to get edge from
 * @param src source node
 * @param dst destiny node
 */
float get_edge(graph * g, int src, int dst);

int get_size(graph * g);

/**
 * Prints a graph
 * @param g graph to print
 */
void print_graph(graph * g);

/**
 * Frees a graph
 * @param g graph to free
 */
void free_graph(graph * g);

/**
 * Finds the shortest path from a node to all the other ones
 * @param g graph to analyze
 * @param src source node
 * @return a node array with all the paths unsorted
 */
node ** dijkstra(graph * g, int src);

/**
 * Free the nodes array from Dijkstra function
 * @param node array of nodes
 * @param size size of the array
 */
void free_nodes(node ** n, int size);