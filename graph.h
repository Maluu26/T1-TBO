#ifndef graph_h
#define graph_h

#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

typedef struct graph graph;

/**
 * Gets the index of a node
 * @param n node to get id of
 * @return node's id
 */
int get_id(node * n);

/**
 * Gets the minimal distance of a node
 * @param n node to get distance of
 * @return node's distance
 */
double get_distance(node * n);

/**
 * Gets the parent of a node
 * @param n node to get parent of
 * @return node's parent
 */
node * get_parent(node * n);

/**
 * Frees a node
 * @param n node to free
 */
void free_node(node * n);

/**
 * Frees an array of nodes
 * @param n node array
 * @param size array's size
 */
void free_nodes(node ** n, int size);

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
void insert_edge(graph * g, int src, int dst, double w);

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
double get_edge(graph * g, int src, int dst);

/**
 * Gets the size of graph
 * @param g graph to get size of
 * @return size of graph
 */
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

/**
 * Compares which node has the biggest distance
 * @param a node a
 * @param b node b
 * @return 1 if a is bigger, -1 if b is bigger, 0 if equal
 */
int compare_nodes(const void *a, const void *b);

/**
 * Prints a node array in a file
 * @param path node array
 * @param size array's size
 * @param file file to print paths
 */
void print_path_on_file(node **path, int size, FILE *file);

#endif