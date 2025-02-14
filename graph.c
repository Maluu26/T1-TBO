/*
 * Primeiro Trabalho de Técnicas de Busca e Ordenação (2024/02)
 * Feito por Eduardo Silva, Marcela Carpenter e Maria Luiza Reis
 * Fevereiro de 2025
 */

/**
 * Informações gerais (Eduardo):
 * 1. Esse arquivo deveria ter sido dividido em mais TADs (a lista podia ser genérica...), 
 *    mas como tudo acabou ficando entrelaçado, decidi manter em um único mesmo
 * 2. Apenas as funções mais relevantes (no caso, as referentes a Dijkstra) foram comentadas
 *    e estão mais ao fim desse arquivo
 */

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

// Código dos Nós

struct node {
    int id;
    double dist;
    node * prt;
    node * next;
};

node * create_node(int id, double dist, node * prt) {

    node * n = (node *) calloc(1, sizeof(node));
    n -> id = id;
    n -> dist = dist;
    n -> prt = prt;

return n;
}

node ** create_nodes(int size) {

    node ** ns = (node **) calloc(size, sizeof(node *));

    for(int i = 0; i < size; i++) {
        ns[i] = create_node(i, INFINITY, NULL);
    }

return ns;
}

int get_id(node * n) {
    return n -> id;
}

double get_distance(node * n) {
    return n -> dist;
}

node * get_parent(node * n) {
    return n -> prt;
}

node * get_next(node * n) {
    return n -> next;
}

void set_distance(node * n, double new_distance) {
    n -> dist = new_distance;
}

void set_parent(node * n, node * prt_id) {
    n -> prt = prt_id;
}

void set_next(node * n, node * nxt) {
    n -> next = nxt;
}

void free_node(node * n) {
    free(n);
}

// Essa função remove os nós recursivamente na lista
void free_nodes_list(node * n) {
    if(get_next(n) != NULL) free_nodes_list(get_next(n));
    free(n);
}

void free_nodes(node ** n, int size) {

    for(int i = 0; i < size; i++) {
        free(n[i]);
    }
    free(n);

}

// Código da Lista

typedef struct list list;

struct list {
    node * first;
    node * last;
};

void init_list(list * l) {
    l -> first = NULL;
    l -> last = NULL;
}

void insertl(list * l, int id, double dist) {
    
    node * n = create_node(id, dist, NULL);

    if(l -> first == NULL) {
        l -> first = n;
        l -> last = n;
    }
    else {
        set_next(l -> last, n);
        l -> last = n;
    }
    
}

void removel(list * l, int id) {

    if(!l -> first) return;

    node * last = NULL;
    node * checker = l -> first;

    while(checker && get_id(checker) != id) {
        last = checker;
        checker = get_next(checker);
    }

    if(checker == l -> first) {
        l -> first = NULL;
        l -> last = NULL;
    }
    else if(checker == l -> last) {
        set_next(last, NULL);
        l -> last = last;
    }
    else {
        set_next(last, get_next(checker));
    }
    free_node(checker);

}

double findl(list * l, int id) {

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

// Código do Grafo

struct graph {
    int size;
    list ** ns_list;
};

// Nosso grafo é uma vetor de listas, assim podemos indexar um nó e procurar suas conexões caminhando na lista
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
    insertl(g -> ns_list[src], dst, w);

}

void remove_edge(graph * g, int src, int dst) {

    if(size_error(src, dst, get_size(g))) return;
    removel(g -> ns_list[src], dst);

}

double get_edge(graph * g, int src, int dst) {
    return findl(g -> ns_list[src], dst);
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

// Verifica se a distância atual no vetor de nós é menor que a encontrada atualmente, se for, troca o valor e seta o novo pai
int relax(node ** ns, node * checker, int id) {

    if(get_distance(ns[get_id(checker)]) > get_distance(checker) + get_distance(ns[id])) {
        set_distance(ns[get_id(checker)], get_distance(checker) + get_distance(ns[id]));
        set_parent(ns[get_id(checker)], ns[id]);
        return 1;
    }

return 0;
}

/**
 * A implementação dessa função foi feita após uma aula de Teoria dos Grafos e, portanto, segue
 * um pseudocódigo sugerido pelo professor Berilhes Borges Garcia, sendo ele: 
 * 
 * Dijkstra(G, w, s)
 *  for cada vértice v pertencente G.V
 *      v.pai <- Null
 *      v.d <- Infinito
 *  s.d <- 0
 * 
 *  Construa_Fila_Prioridade(Q, G.V)
 *  
 *  while Q != VAZIO :
 *      u <- Extrair_Minimo(Q)
 *      for cada vértice v adjacente à u
 *      Relaxe((u, v))
 *      Decresça_Chave(Q, v, v.d)
 * 
 * Resumidamente, esse pseudocódigo cria uma fila de prioridades em que os vértices são inseridos nela com valores infinitos, a exceção do source.
 * Este recebe distância 0 e é o primeiro da fila. Cada vez que um valor é removido da fila, os outros vértices tem suas distâncias atualizadas
 * caso sejam alcançados pelo anterior analisado. A função Relaxe identifica se um valor menor foi encontrado e o atualiza. Isso é feito até que a
 * fila esteja vazia. Cada vértice analisado é removido da fila.
 */
node ** dijkstra(graph * g, int src) {

    int min_id = 0;

    // Um vetor de nós é criado para armazenar os vértices do grafo, esse vetor será retornado com os menores caminhos
    node ** ns = create_nodes(get_size(g));
    set_distance(ns[src], 0);
    set_parent(ns[src], ns[src]);

    // A fila com prioridade é criada e todos os vértices são inseridos nela também
    PQ * hp = createPQ(get_size(g));
    for(int i = 0; i < get_size(g); i++) {
        insertIntoPQ(hp, get_distance(ns[i]), i);
    }
    
    // Enquanto a fila não está vazia, continuamos verificando
    while(!isPQEmpty(hp)) {

        // Recebemos o index do primeiro item (o que possui menor distância) e ele é removido da fila
        min_id = removeFromPQ(hp);

        // Apenas para casos de verificação, se chegarmos em um vértice com valor infinito na fila, podemos parar também
        if(get_distance(ns[min_id]) == INFINITY) break; 
        
        // O checker é um nó temporário que vai rodar a lista de adjacências do vértice analisado e relaxá-los quando necessário
        node * checker = get_first(g -> ns_list[min_id]);
        while(checker) {
            if(relax(ns, checker, min_id)) changePositionInPQ(hp, get_id(checker), get_distance(ns[get_id(checker)]));
            checker = get_next(checker);
        }
    }

    // Liberação de memória da fila
    destroyPQ(hp);

return ns;
}

// Função de comparação para uso do qsort nativo na main
int compare_nodes(const void *a, const void *b){
    node *n1 = *(node **)a;
    node *n2 = *(node **)b;
    if(n1 -> dist > n2 -> dist) return 1;
    else if(n1 -> dist < n2 -> dist) return -1;
    return 0;
}

// Os caminhos são printados recursivamente em arquivo, acessando os seus pais até chegar no source
void print_path(FILE * file, node * n) {

    if(get_id(get_parent(n)) == get_id(n)) {
        fprintf(file, "node_%d ", get_id(n));
        return;
    }
    fprintf(file, "node_%d <- ", get_id(n));    
    print_path(file, get_parent(n));

}

void print_path_on_file(node **path, int size, FILE *file){

    // O primeiro item é printado de forma distinta no arquivo, pois ele é o único que aponta pra si mesmo, já o restante entra no for
    fprintf(file, "SHORTEST PATH TO node_%d: node_%d <- node_%d (Distance: %.2f)\n", get_id(path[0]), get_id(path[0]), get_id(path[0]), get_distance(path[0]));
    
    for(int i = 1; i < size; i++){
        fprintf(file, "SHORTEST PATH TO node_%d: ", get_id(path[i]));
            print_path(file, path[i]);
            fprintf(file, "(Distance: %.2f)\n", get_distance(path[i]));
    }
}