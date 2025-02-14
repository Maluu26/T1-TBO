/*
 * Primeiro Trabalho de Técnicas de Busca e Ordenação (2024/02)
 * Feito por Eduardo Silva, Marcela Carpenter e Maria Luiza Reis
 * Fevereiro de 2025
 */

#ifndef PQ_H
#define PQ_H
#include<stdbool.h>
typedef struct pq PQ;

/***
 * Verifies if the priority queue is valid
 * @param queue priority queue
 */
bool valid_queue(PQ *queue);
/***
 * Verifies if the priority queue is empty
 * @param queue priority queue
 */
bool isPQEmpty(PQ *queue);
/***
 * Creates a priority queue
 * @param size size of the priority queue, according to the number of nodes;
 * @return a priority queue;
 */
PQ *createPQ(int size);
/***
 *
 * @param queue priority queue
 * @param node the node that needs to put in order
 * @param i the position that fix up will start from
 * 
 */
void fixUp(PQ *queue, int node,int i);

/*** 
 * Puts a new value in the priority queue
 * @param queue priority queue
 * @param minDistance the new value
 * @param node the node that needs to put in order
 * 
 */

void insertIntoPQ(PQ *queue,float minDistance, int node);
/***
 * The function will adjust the position of the element on index k
 * @param queue priority queue
 * @param k start of the function
 */
void fixDown(PQ *queue, int k);

/*** 
 * Returns the minimal value of the priority queue and decreases its size;
 * @param queue priority queue
 * @return the node associated with the minimal value of the priority queue
 */
int removeFromPQ(PQ *queue);
/***
 * Alters the previous distance of a node to a new smaller one and adjusts its position ;
 * @param queue priority queue
 * @param  nodeIndex position of the node inside the priority queue
 * @param distance the new smaller distance
 * 
 */
void changePositionInPQ(PQ *queue, int nodeIndex, float distance);
/***
 * @param queque priority queue
 * @return size of the priority queue
 */
int getPQSize(PQ *queue);
/***
 * @param queque priority queue
 * @return the minimal value inside of the priority queue
 */
float returnMinDist(PQ *queue);

/***
 * @param queque priority queue
 * @return node of the minimal value inside of the priority queue
 */
int returnMinIndex(PQ *queue);
/***
 * Frees the memory space occupied
 * @param queque priority queue
 * 
 */
void destroyPQ(PQ *queue);

#endif