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

int findNode(int *vet, int value, int maxnodes){
    if(vet){
        for(int i = 0; i<maxnodes;i++){
            if(vet[i]==value) return i;
        }
    }
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
    
    if(!valid_queue(queue)) return;
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

float returnMinDist(PQ *queue){
   
    if(!valid_queue(queue)) return -1;
    return queue->heap[1].distance;

}
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

