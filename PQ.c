#include"PQ.h"
#include"item.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct pq{
    int *queuePositions;
    float *heap;
    int maxnodes;
    int size;
};
bool valid_queue(PQ *queue){
    
    if(!queue){
        printf("Invalid priority queue!!!");
        return 0;
    }
    return 1;
}
bool isPQEmpty(PQ *queue){
    
    if(!valid_queue(queue)) return;
    return (queue->size == 0);

}

PQ *createPQ(int size){

    PQ *heap = malloc(sizeof(PQ));
    heap->size = 0;
    heap->maxnodes = size;
    heap->heap = malloc(sizeof(float)*(size+1));
    heap->queuePositions = malloc(sizeof(int)*(size));
    
    for(int i = 0;i<heap->maxnodes;i++){
        heap->queuePositions[i] = -1;
        heap->heap[i] = 10000000;
    }
    heap->heap[size] = -1;
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
   
   
   while(i>1 && less(queue->heap[i], queue->heap[i/2])){
        int newPosition = findNode(queue->queuePositions, i/2 ,queue->maxnodes);
        exch(queue->heap[i], queue->heap[i/2]);
        exch(queue->queuePositions[node], queue->queuePositions[newPosition]);
        i = i/2;  
   }

}
void insertIntoPQ(PQ *queue,float minDistance, int node){
    
    if(!valid_queue(queue)) return;
    queue->size++;
    queue->heap[queue->size] = minDistance;
    queue->queuePositions[node] = queue->size;
    fixUp(queue, node, queue->size);
    
}

void fixDown(PQ *queue, int k){
    
    if(!valid_queue(queue)) return;
    
   
    while(k*2<=queue->size){
        int j = k*2;
        
        if (j < queue->size && queue->heap[j] > queue->heap[j+1]){
                j++;
            }
        if (!(queue->heap[k]>queue->heap[j])) {
            break;
        }
        
        exch(queue->heap[k], queue->heap[j]);
        int p1 = findNode(queue->queuePositions, k,queue->maxnodes);
        int p2 = findNode(queue->queuePositions, j, queue->maxnodes);
        exch(queue->queuePositions[p1], queue->queuePositions[p2]);
        k = j;
        }

}
float removeFromPQ(PQ *queue){
   
    if(!valid_queue(queue)) return;

    int p1 = findNode(queue->queuePositions, 1,queue->maxnodes);
    int p2 = findNode(queue->queuePositions, queue->size, queue->maxnodes);
    exch(queue->heap[1], queue->heap[queue->size]);
    exch(queue->queuePositions[p1], queue->queuePositions[p2]);
    queue->size--;
    fixDown(queue, 1);
    return queue->heap[queue->size+1];

}

void changePositionInPQ(PQ *queue, int nodeIndex, float distance){

    if(!valid_queue(queue)) return;
    int position = queue->queuePositions[nodeIndex];
    queue->heap[position] = distance;
    fixUp(queue,nodeIndex, position);
    
     
}

int getPQSize(PQ *queue){   
   
    if(!valid_queue(queue)) return;
    return queue->size;
   
}

float returnMin(PQ *queue){
   
    if(!valid_queue(queue)) return;
    return queue->heap[1];

}
void destroyPQ(PQ *queue){   
    
    if(!valid_queue(queue)) return;
    free(queue->heap);
    free(queue->queuePositions);
    free(queue);

}

