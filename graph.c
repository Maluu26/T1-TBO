#include "graph.h"
#include "colors.h"

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

struct node {
    int id;
    float dist;
    int prt;
};

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

void insert_edge(graph * g, int src, int dst, float w) {

    if(size_error(src, dst, g -> size)) return;
    g -> matrix[src][dst] = w;

}

void remove_edge(graph * g, int src, int dst) {

    if(size_error(src, dst, g -> size)) return;
    g -> matrix[src][dst] = 0;

}

float get_edge(graph * g, int src, int dst) {
    return g -> matrix[src][dst];
}

void print_graph(graph * g) {

    for(int i = 0; i < g -> size; i++) {
        for(int j = 0; j < g -> size; j++) {
            float v = g -> matrix[i][j];
            if(v == 0) printf("%.1f ", v);
            else printf("%s%.1f %s", CYAN, v, RESET);
        }
        printf("\n");
    }

}

void free_graph(graph * g) {

    for(int i = 0; i < g -> size; i++) {
        free(g -> matrix[i]);
    }
    free(g -> matrix);
    free(g);

}

node ** dijkstra(graph * g, int src) {

    //implement dijkstra!!

}

void free_nodes(node ** n, int size) {

    for(int i = 0; i < size; i++) {
        free(n[i]);
    }
    free(n);

}