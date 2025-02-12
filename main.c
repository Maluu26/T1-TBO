#include<stdio.h>
#include<stdlib.h>
#include"PQ.h"

int main(){
    PQ *pq = createPQ(6);
    insertIntoPQ(pq, 6, 0);
    insertIntoPQ(pq, 17, 1);
    insertIntoPQ(pq, 12, 2);
    insertIntoPQ(pq, 7, 3);
    insertIntoPQ(pq, 10, 4);
    insertIntoPQ(pq, 15, 5);
    changePositionInPQ(pq,5, 5);
    removeFromPQ(pq);
    float dist = returnMinDist(pq);
    destroyPQ(pq);



}