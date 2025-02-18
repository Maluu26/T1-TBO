/*
 * Primeiro Trabalho de Técnicas de Busca e Ordenação (2024/02)
 * Feito por Eduardo Silva(2023100580), Marcela Carpenter(2023100260)
 *  e Maria Luiza Reis(2023101579)
 * Fevereiro de 2025
 */


#ifndef queue_h
#define queue_h

#include<stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct queue queue;

 /**
  * Cria e inicializa uma nova fila
  * @return nova fila criada
  */
queue *create_queue();

 /**
  * Verifica se a fila está vazia
  * @param q fila a ser verificada
  * @return true se a fila estiver vazia, false caso contrário
  */
bool is_queue_empty(queue *q);
 
 /**
  * Insere um novo item na fila
  * @param q fila onde o nó será inserido
  * @param dist distância do nó
  * @param id identificador do nó
  */
void insert_into_queue(queue *q, double dist, int id);
 
 /**
  * Remove o item com a menor distância na fila
  * @param q fila onde será feita a remoção
  * @return ID do nó removido ou -1 se a fila estiver vazia
  */
int remove_from_queue(queue *q); 
 
 /**
  * Atualiza a distância de um nó na fila
  * @param q fila
  * @param id identificador do nó
  * @param new_distance nova distância a ser atribuída
  */
void change_distance_in_queue(queue *q, int id, double new_distance);

 /**
  * Libera a memória alocada para a fila
  * @param q fila a ser liberada
  */
void free_queue(queue *q);

#endif