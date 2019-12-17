#include "readData.h"
#include "globalAl.h"
#include "localAl.h"
#include <stdlib.h>	
#include <string.h>
#include <stdio.h>

int main(int argc, char** argv){
    int i;
    // Si no hay n argumentos pares FUERA
    
    if(argc < 4){
        perror("Wrong number of inputs, take a look at the readMe");
        return -1;
    }
    
    for(i = 2; i < argc; i+=2){
        
        /*argv[i] corresponds to the name of the data file, argv[i+1] to the query file*/
        printf("\n===================\n");
        /*Get the lenght of both alignments*/
        int dlenght = getFASTALenght(argv[i]);
        printf("the lenght of the database secuence is %d\n", dlenght);
        int qlenght = getFASTALenght(argv[i + 1]);
        printf("the lenght of the query secuence is %d\n", qlenght);
        
        char dAlig[dlenght];
        char qAlig[qlenght];
        
        /*Save the alignments from the files*/
        if(!readFASTA(argv[i], dAlig, dlenght)){
            printf("Error reading the file %s", argv[i]);
            return 0;
        }
        if(!readFASTA(argv[i + 1], qAlig, qlenght)){
            printf("Error reading the file %s", argv[i]);
                return 0;
        }
        printf("\n");
        printf("database sequence > %s\n", dAlig);
        printf("query sequence > %s\n", qAlig);
        
        /** We run the algorithm for Global Alignment**/
        if(!strcmp(argv[1], "global")){
            int maxScore = globalAlign(dAlig, qAlig, dlenght+1, qlenght+1);
            printf("\nMax score for the alignments is %d\n", maxScore); 
        }
        
        /** We run the algorithm for Local Alignment**/
        else if(!strcmp(argv[1], "local")){
            //deberia devolver los subalignments
            localAlign(dAlig, qAlig, dlenght+1, qlenght+1);
        }
    
        else{
            perror("Error with argv[1], try with 'local' or 'global' ");
            return -1;
        }
    }
    return 0;
}