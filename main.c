#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Files not found!\n");
        return 1;
    }
    
    char input_name[100], output_name[100];
    FILE *input_file, *output_file;

    sprintf(input_name, "%s", argv[1]);
    sprintf(output_name, "%s", argv[2]);

    input_file = fopen(input_name, "r");
    if (!input_file) {
        printf("Error opening the file %s!\n", input_name);
        return 1;
    }

    char source_node[7], bomb[7];
    double dist=0;
    int size=1;

    //Read and discard the firts line and the firts node's name 
    fscanf(input_file, "%*[^\n]%*c");
    fscanf(input_file, "%*[^,]%*c");

    //Read the first line, finding the size by the number of columns   
    while(1){
        if(fscanf(input_file, "%lf", &dist) == 1);
        else (fscanf(input_file, "%s", bomb));
        fscanf(input_file, "%[ \n,]", bomb);
        size++;
        if(bomb[0] == '\n') break;
    }
    
    graph * g =  create_graph(size);

    rewind(input_file);

    //Read the source node
    fscanf(input_file, "%[^\n]\n", source_node); // linha provisória!
    for(int i=0; i < size; i++){
        
        //Discard the name of the node
        fscanf(input_file, "%*[^,],");
        
        for(int j=0; j < size; j++){
            if(i == j) insert_edge(g, i, j, 0);
            
            else{
                if(fscanf(input_file, "%lf", &dist) == 1){
                    insert_edge(g, i, j, dist);
                }
                else {
                    fscanf(input_file, "%s", bomb);
                    insert_edge(g, i, j, 0);
                }
                fscanf(input_file, "%[ \n,]", bomb);
            }
            
        } 
    }
    
    //print_graph(g);

    free(g);
    fclose(input_file);
    return 0;
}