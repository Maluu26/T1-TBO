#include "graph.h"
#include "colors.h"
#include <math.h>
#include "PQ.h"

int size_error(int src, int dst, int size) {

    if(src >= size || dst >= size) {
        printf("%sERROR: Edge from %d to %d could not be inserted. Source or destiny node is bigger than graph's size\n%s",
        RED, src, dst, RESET);
        return 1;
    }
    else if(src < 0 || dst < 0) {
        printf("%sERROR: Edge from %d to %d could not be inserted. Source or destiny node is smaller than graph's size\n%s",
        RED, src, dst, RESET);
        return 1;  
    }

return 0;
}

// Node related code

struct node {
    int id;
    float dist;
    int prt;
};

node * create_node(int id, float dist, int prt) {

    node * n = (node *) calloc(1, sizeof(node));
    n -> id = id;
    n -> dist = dist;
    n -> prt;

return n;
}

node ** create_nodes(int size) {

    node ** ns = (node **) calloc(size, sizeof(node *));

    for(int i = 0; i < size; i++) {
        ns[i] = create_node(i, INFINITY, -1);
    }

return ns;
}

int get_id(node * n) {
    return n -> id;
}

float get_distance(node * n) {
    return n -> dist;
}

int get_parent(node * n) {
    return n -> prt;
}

void set_distance(node * n, float new_distance) {
    n -> dist = new_distance;
}

void set_parent(node * n, int prt_id) {
    n -> prt = prt_id;
}

// Graph related code

struct graph {
    int size;
    float ** matrix;
};

graph * create_graph(int size) {

    if(size <= 0) {
        printf("%sERROR: Informed size to create graph is 0 or smaller\n%s",
        RED, RESET);
        return NULL;
    }
    graph * g = (graph *) calloc(1, sizeof(graph));

    g -> size = size;
    g -> matrix = (float **) calloc(size, sizeof(float *));

    for(int i = 0; i < size; i++) {
        g -> matrix[i] = (float *) calloc(size, sizeof(float));
    }

return g;
}

int get_size(graph * g) {
    return g -> size;
}

void insert_edge(graph * g, int src, int dst, float w) {

    if(size_error(src, dst, get_size(g))) return;
    g -> matrix[src][dst] = w;

}

void remove_edge(graph * g, int src, int dst) {

    if(size_error(src, dst, get_size(g))) return;
    g -> matrix[src][dst] = 0;

}

float get_edge(graph * g, int src, int dst) {
    return g -> matrix[src][dst];
}

void print_graph(graph * g) {

    for(int i = 0; i < get_size(g); i++) {
        for(int j = 0; j < get_size(g); j++) {
            float v = g -> matrix[i][j];
            if(v == 0) printf("%.1f ", v);
            else printf("%s%.1f %s", CYAN, v, RESET);
        }
        printf("\n");
    }

}

void free_graph(graph * g) {

    for(int i = 0; i < get_size(g); i++) {
        free(g -> matrix[i]);
    }
    free(g -> matrix);
    free(g);

}

void relax(node ** ns, int id) {

    for()

}

node ** dijkstra(graph * g, int src) {

    int min_id = 0;

    node ** ns = create_nodes(get_size(g));
    set_distance(ns[src], 0);
    set_parent(ns[src], src);

    PQ * hp = createPQ(get_size(g));
    for(int i = 0; i < get_size(g); i++) {
        insertIntoPQ(hp, get_distance(ns[i]), i);
    }
    
    while(!isPQEmpty(hp)) {
        // waiting for fix in pq
        break;
    }

    destroyPQ(hp);

return ns;
}

void free_nodes(node ** n, int size) {

    for(int i = 0; i < size; i++) {
        free(n[i]);
    }
    free(n);

}