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

// NODE RELATED CODE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

struct node {
    int id;
    double dist;
    int prt;
    node * next;
};

node * create_node(int id, double dist, int prt) {

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

double get_distance(node * n) {
    return n -> dist;
}

int get_parent(node * n) {
    return n -> prt;
}

node * get_next(node * n) {
    return n -> next;
}

void set_distance(node * n, double new_distance) {
    n -> dist = new_distance;
}

void set_parent(node * n, int prt_id) {
    n -> prt = prt_id;
}

void set_next(node * n, node * nxt) {
    n -> next = nxt;
}

void free_node(node * n) {
    free(n);
}

void free_nodes_list(node * n) {
    if(get_next(n) != NULL) free_nodes_list(get_next(n));
    free(n);
}

void free_nodes_array(node ** n, int size) {

    for(int i = 0; i < size; i++) {
        free(n[i]);
    }
    free(n);

}

// LIST RELATED CODE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

typedef struct list list;

struct list {
    node * first;
    node * last;
};

void init_list(list * l) {
    l -> first = NULL;
    l -> last = NULL;
}

void insert(list * l, int id, double dist) {
    
    node * n = create_node(id, dist, -1);

    if(l -> first == NULL) {
        l -> first = n;
        l -> last = n;
    }
    else {
        set_next(l -> last, n);
        l -> last = n;
    }
    
}

double find(list * l, int id) {

    if(!l -> first) return 0;

    node * checker = l -> first;
    while(checker && get_id(checker) != id) {
        checker = get_next(checker);
    }

    if(checker) return get_distance(checker);
    else return 0;

}

void print_list(list * l) {

    node * checker = l -> first;
    while(checker) {
        printf("node %d (%.1f) ", get_id(checker), get_distance(checker));
        checker = get_next(checker);
    }

}

node * get_first(list * l) {
    return l -> first;
}

void free_list(list * l) {

    if(!l -> first) {
        free(l);
        return;
    }

    free_nodes_list(l -> first);
    free(l);

}

// GRAPH RELATED CODE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

struct graph {
    int size;
    list ** ns_list;
};

graph * create_graph(int size) {

    if(size <= 0) {
        printf("%sERROR: Informed size to create graph is 0 or smaller\n%s",
        RED, RESET);
        return NULL;
    }
    graph * g = (graph *) calloc(1, sizeof(graph));

    g -> size = size;
    g -> ns_list = (list **) calloc(size, sizeof(list *));

    for(int i = 0; i < size; i++) {
        g -> ns_list[i] = (list *) calloc(size, sizeof(list));
        init_list(g -> ns_list[i]);
    }

return g;
}

int get_size(graph * g) {
    return g -> size;
}

void insert_edge(graph * g, int src, int dst, double w) {

    if(size_error(src, dst, get_size(g))) return;
    insert(g -> ns_list[src], dst, w);

}

//void remove_edge(graph * g, int src, int dst) {
//
//    if(size_error(src, dst, get_size(g))) return;
//    g -> matrix[src][dst] = 0;
//
//}

double get_edge(graph * g, int src, int dst) {
    return find(g -> ns_list[src], dst);
}

void print_graph(graph * g) {

    for(int i = 0; i < get_size(g); i++) {
        printf("%sNODE %d Adjacency List:%s ", GREEN, i, RESET);
        print_list(g -> ns_list[i]);
        printf("\n");
    }

}

void free_graph(graph * g) {

    for(int i = 0; i < get_size(g); i++) {
        free_list(g -> ns_list[i]);
    }
    free(g -> ns_list);
    free(g);

}

int relax(node ** ns, node * checker, int id) {

    if(get_distance(ns[get_id(checker)]) > get_distance(checker) + get_distance(ns[id])) {
        set_distance(ns[get_id(checker)], get_distance(checker));
        set_parent(ns[get_id(checker)], id);
        return 1;
    }

return 0;
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
        //TO DO!!!!!!!!!!!!!!!!!!!!!
        int id = 0; //THIS ID SHOULD BE RETURNED FROM PQ DELMIN
        node * checker = get_first(g -> ns_list[id]);
        while(checker) {
            if(relax(ns, checker, id)) changePositionInPQ(hp, get_id(checker), get_distance(ns[get_id(checker)]));
        }
        break;
    }

    destroyPQ(hp);

return ns;
}