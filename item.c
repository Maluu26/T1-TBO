#include"item.h"
#include<stdlib.h>
#include<stdio.h>
Item *criaVetor(int N){
    Item *i = malloc(sizeof(Item)*N);
    return i;
}
void fillArray(FILE *inputs, int N, Item *i){
    if(!i || !inputs) return;
    for(int j = 0;j<N;j++){
         fscanf(inputs,"%d\n",&i[j]);
    }
    fclose(inputs);
}
void printArray( int N, Item *i){
    if(!i ) return;
    FILE *arqPronto = fopen("ordenado.txt", "w");
    for(int j = 0;j<N;j++){
         fprintf(arqPronto,"%d\n",i[j]);
    }
    fclose(arqPronto);
}