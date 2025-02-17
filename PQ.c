/*
 * Primeiro Trabalho de Técnicas de Busca e Ordenação (2024/02)
 * Feito por Eduardo Silva(2023100580), Marcela Carpenter(2023100260)
 *  e Maria Luiza Reis(2023101579)
 * Fevereiro de 2025
 */

/*Como essa implementação de fila de prioridades segue o formarto seguido
em sala, com poucas alterações, e ponto h está comentado são feitos poucos
comentários neste arquivo
*/
#include"PQ.h"
#include"item.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct pqItem {
    float distance;
    int index;
}PQItem ;


struct pq{
    int *queuePositions;
    PQItem *heap;
    int maxnodes;
    int size;
};

void exchPQ(PQItem *p, int index1, int index2){
    PQItem aux = p[index1];
    p[index1] = p[index2];
    p[index2]= aux;

}
bool valid_queue(PQ *queue){
    
    if(!queue){
        printf("Invalid priority queue!!!");
        return 0;
    }
    return 1;
}
bool isPQEmpty(PQ *queue){
    
    if(!valid_queue(queue)) return true;
    return (queue->size == 0);

}
/***
 * Nessa funcao é criada a fila de prioridades com os seguintes campos:
 * tamanho atual (size), tamanho maximo (maxnodes), heap (uma heap com as
 * informacoes de distancia e a identificacao do node), queuePositions (um vetor
 * auxiliar que fala em qual posicao da heap cada node esta)
 */
PQ *createPQ(int size){

    PQ *heap = malloc(sizeof(PQ));
    heap->size = 0;
    heap->maxnodes = size;
    heap->heap = malloc(sizeof(PQItem)*(size+1));
    heap->queuePositions = malloc(sizeof(int)*(size));
    
    for(int i = 0;i<heap->maxnodes;i++){
        heap->heap[i].index = -1;
        heap->heap[i].distance = 10000000;
        heap->queuePositions[i] = -1;
    }
    heap->heap[size].index = -1;
    heap->heap[size].distance = 10000000;
   
    return heap;

}

void fixUp(PQ *queue, int node, int i){
   
   if(!valid_queue(queue)) return;
   
   
   while(i>1 && less(queue->heap[i].distance, queue->heap[i/2].distance)){
        int newPosition = queue->heap[i/2].index;
        exchPQ(queue->heap,i, i/2);
        exch(queue->queuePositions[node], queue->queuePositions[newPosition]);
        i = i/2;  
   }

}
void insertIntoPQ(PQ *queue,float minDistance, int node){
    
    if(!valid_queue(queue)|| queue->size == queue->maxnodes)  return;
    queue->size++;
    queue->heap[queue->size].distance = minDistance;
    queue->heap[queue->size].index = node;
    queue->queuePositions[node] = queue->size;
    fixUp(queue, node, queue->size);
    
}

void fixDown(PQ *queue, int k){
    
    if(!valid_queue(queue)) return;
   
    while(k*2<=queue->size){
        int j = k*2;
            
        if (j < queue->size && queue->heap[j].distance > queue->heap[j+1].distance){
                    j++;
        }
        if (!(queue->heap[k].distance>queue->heap[j].distance)) {
            break;
        }
        int p1 = queue->heap[j].index;
        int p2 = queue->heap[k].index;
        exchPQ(queue->heap,k, j);
        exch(queue->queuePositions[p1], queue->queuePositions[p2]);
        k = j;
    }
    
}
int removeFromPQ(PQ *queue){
   
    if(!valid_queue(queue)) return -1;

    int p1 = queue->heap[1].index;
    int p2 = queue->heap[queue->size].index;
    exch(queue->queuePositions[p1], queue->queuePositions[p2]);
    exchPQ(queue->heap,1,queue->size);
    
    queue->size--;
    fixDown(queue, 1);
    return queue->heap[queue->size+1].index;

}
/***
 * Coloca o novo menor valor e chama o fixUp para ajustar a posição dele
 * na fila de prioridades
 */
void changePositionInPQ(PQ *queue, int nodeIndex, float distance){

    if(!valid_queue(queue)) return;
    int position = queue->queuePositions[nodeIndex];
    queue->heap[position].distance = distance;
    fixUp(queue,nodeIndex, position);
    
     
}

int getPQSize(PQ *queue){   
   
    if(!valid_queue(queue)) return 0;
    return queue->size;
   
}
/***
    Retorna a distância mínima da heap;
 */
float returnMinDist(PQ *queue){
   
    if(!valid_queue(queue)) return -1;
    return queue->heap[1].distance;

}/***
    Retorna o node que é o valor mínimo da heap;
 */
int returnMinIndex(PQ *queue){
   
    if(!valid_queue(queue)) return -1;
    return queue->heap[1].index;

}
void destroyPQ(PQ *queue){   
    
    if(!valid_queue(queue)) return;
    free(queue->heap);
    free(queue->queuePositions);
    free(queue);

}

