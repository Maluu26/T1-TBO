/*
 * Primeiro Trabalho de Técnicas de Busca e Ordenação (2024/02)
 * Feito por Eduardo Silva(2023100580), Marcela Carpenter(2023100260)
 *  e Maria Luiza Reis(2023101579)
 * Fevereiro de 2025
 */



#include "queue.h"
#include <math.h>

typedef struct q_item q_item;

struct q_item {
    double distance;
    int id;
    q_item *next;
};

struct queue {
    q_item *head, *bottom;
};

int get_item_id(q_item *item){
    return item->id;
}

double get_item_dist(q_item *item){
    return item->distance;
}

queue *create_queue(int size){
    queue *q = malloc(sizeof(queue));
    q->head = q->bottom = NULL;
    
    return q;
}

bool is_queue_empty(queue *q){
    if(!q->head) return true;
    else return false; 
}

void insert_into_queue(queue *q, double dist, int id){
    if(!q) return;
    
    q_item *new = malloc(sizeof(q_item));
    new->id = id;
    new->distance = dist;
    new->next = NULL;

    if(!q->head){
        q->head = new;
    }
    else {
        q->bottom->next = new;
    }
    q->bottom = new;
}

q_item *find_item(queue *q, int id){
    if(!q) return NULL;

    q_item *temp = q->head;
    
    while(temp && (get_item_id(temp) != id)){
        temp = temp->next;
    }

    return temp;
}

void remove_item(queue *q, int id){
    if(!q) return;

    q_item *prev = NULL, *temp = q->head;
    
    while(temp && (get_item_id(temp) != id)){
        prev = temp;
        temp = temp->next;
    }
    
    if(q->head == temp && q->bottom == temp){
        q->head = q->bottom = NULL;
    }
    else if(q->head == temp){
        q->head = temp->next;
    }
    else if(q->bottom == temp){
        q->bottom = prev;
        prev->next = NULL;
    }
    else {
        prev->next = temp->next;
    }
    
    free(temp);
}

int remove_from_queue(queue *q){
    if(!q) return -1;
    
    int min_id = -1;
    double min_dist = INFINITY;
    
    q_item *temp = q->head;
    
    while(temp){
        if(less(get_item_dist(temp), min_dist)){
            min_dist = get_item_dist(temp);
            min_id = get_item_id(temp);
        }
        temp = temp->next;
    }
    
    remove_item(q, min_id);
    
    return min_id;
}

void change_distance_in_queue(queue *q, int id, double new_distance){
    if(!q) return;
    
    q_item *i = find_item(q, id);
    i->distance = new_distance;
}

void free_queue(queue *q){
    if(!q) return;
    free(q);
}