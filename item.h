#ifndef item_h
#define item_h 
#include<stdio.h>
typedef int Item;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B) { Item t = A; A = B; B = t; }
#define compexch(A, B) if (less(B, A)) exch(A, B)
Item *criaVetor(int N);
void fillArray(FILE *inputs, int N, Item *i);
void printArray( int N, Item *i);
#endif