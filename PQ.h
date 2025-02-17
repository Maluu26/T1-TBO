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
 * Verifica se a fila de prioridades é válida
 * @param queue fila de prioridades
 */
bool valid_queue(PQ *queue);
/***
 * Verifica se a fila de prioridades está vazia
 * @param queue fila de prioridades
 */
bool isPQEmpty(PQ *queue);
/***
 * Cria a fila de prioridades
 * @param size tamanho da fila de prioridades, de acordo com o
 * número de nós;
 * @return a fila de prioridades;
 */
PQ *createPQ(int size);
/***
 *
 * @param queue fila de prioridades
 * @param node o nó que precisa ser ordenado
 * @param i a posição de onde o fix up vai começar
 * 
 */
void fixUp(PQ *queue, int node,int i);

/*** 
 * Coloca um novo valor na fila de prioridades
 * @param queue fila de prioridades
 * @param minDistance o novo valor
 * @param node o node que precisa ser colocado em ordem
 * 
 */

void insertIntoPQ(PQ *queue,float minDistance, int node);
/***
 * A função irá ajustar a posição do elemento no index k
 * @param queue fila de prioridades
 * @param k podicao de inicio da função
 */
void fixDown(PQ *queue, int k);

/*** 
 * Retorna o node que era o valor mínimo da fila de prioridades e diminui o tamanho dela;
 * @param queue fila de prioridades
 * @return o node removido associado com o valor mínimo da fila de prioridades 
 */
int removeFromPQ(PQ *queue);
/***
 * Altera a distância anterior de um node para uma menor e a justa a sua posição na heap ;
 * @param queue fila de prioridades
 * @param  nodeIndex posição do node dentro da fila de prioridades
 * @param distance a nova menor distância
 * 
 */
void changePositionInPQ(PQ *queue, int nodeIndex, float distance);
/***
 * @param queque fila de prioridades
 * @return tamanho da fila de prioridades
 */
int getPQSize(PQ *queue);
/***
 * Retorna a distância mínima da heap;
 * @param queque fila de prioridades
 * @return the minimal value inside of the fila de prioridades
 */
float returnMinDist(PQ *queue);

/***
 * Retorna o node de distância mínima da heap;
 * @param queque fila de prioridades
 * @return node of the minimal value inside of the fila de prioridades
 */
int returnMinIndex(PQ *queue);
/***
 * Libera o espaço de memória ocupado pela fila de prioridades
 * @param queque fila de prioridades
 * 
 */
void destroyPQ(PQ *queue);

#endif