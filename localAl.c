#include "localAl.h"
#include "readData.h"
#include "stack.h"
#include <stdlib.h>	
#include <string.h>
#include <stdio.h>

/*structure used to pass as value the secuences during backtracking*/
struct Align 
{
    char dSeq[MAX_ALIGN];
    char qSeq[MAX_ALIGN];
};


int localAlign(const char* dAlig, const char* qAlig, const int dlenght, const int qlenght){
    
    /*We create the tables required for DP*/
    int table[dlenght][qlenght];
    Align subAl;

    int i, j;/*Counters used to go throw the tables*/
    
    /*Initialization of the first row and column**/
    for(j=0; j < qlenght; j++){
        table[0][j] = 0;
    }
    for(i=1; i < dlenght; i++){
        table[i][0] = 0;
    }
    /*We get the position of the best scoring cells on the stack*/
    struct Stack * maxScorePost = getScoreLA(dlenght, qlenght, table, dAlig, qAlig);
    
    printTable(dlenght, qlenght, table, dAlig, qAlig);
    printf("The max score for any local alignment is: %d.\n", table[getSubTop(maxScorePost)][getTop(maxScorePost)]);
    printf("\n\nAlignments: \n");
    
    /*We call bt function for any max score cell*/
    while(!isEmpty(maxScorePost)){
        backtrackingLA(qlenght, table, dAlig, qAlig, subAl, 0, getSubTop(maxScorePost), getTop(maxScorePost));
        pop(maxScorePost);
        pop(maxScorePost);
    }
    return 1;
}

struct Stack* getScoreLA(const int dlenght, const int qlenght, int (*table)[qlenght], const char* dAlig, const char* qAlig){
    
    //CdE
    int max, globalMax = 0, Rdq;
    struct Stack * globalMaxStack = createStack((dlenght-1)*(qlenght-1));
    int i, j;
    
    for (i = 1; i < dlenght; i++) {
        for (j = 1; j < qlenght; j++) {
            /*We check for match or mismatch in this cell*/
            Rdq = dAlig[i-1] == qAlig[j-1] ? LMATCH : LM_MATCH; 

            max = (table[i-1][j-1] + Rdq) > 0 ? table[i-1][j-1] + Rdq: 0;
            /*Position [i][j] is updated with the optimal score*/
            max =  max > (table[i][j-1] - LGAP_PEN) ? max : table[i][j-1] - LGAP_PEN;
            max =  max > (table[i-1][j] - LGAP_PEN) ? max : table[i-1][j] - LGAP_PEN;
            
            table[i][j] = max;
            
            /*We push the position of the best scoring cell at the moment*/
            if(max == globalMax){
                push(globalMaxStack, i);
                push(globalMaxStack, j);
            }
            if(max > globalMax){//Usar el stack
                globalMax = max;
                
                while(!isEmpty(globalMaxStack)){
                    pop(globalMaxStack);
                }
                push(globalMaxStack, i);
                push(globalMaxStack, j);
            }
        }
    }
    
    return globalMaxStack;
}

void backtrackingLA(int qlenght, int (*table)[qlenght], const char* dAlig, const char* qAlig, Align subAl, int k, int i, int j){
    
    //Condicion de parada, igual debe ir a final en caso de que no se haya entrado en ningun if
    
    int Rdq = dAlig[i-1] == qAlig[j-1] ? LMATCH : LM_MATCH; 
    int aux = 0;
    
    if(table[i][j] == (table[i-1][j] - LGAP_PEN) && (table[i-1][j])){
        subAl.dSeq[k] = dAlig[i-1];
        subAl.dSeq[k] = '-';
        backtrackingLA(qlenght, table, dAlig, qAlig, subAl, k+1, i-1, j);
    }else{
        aux++;
    }
    
    if(table[i][j] == (table[i][j-1] - LGAP_PEN) && (table[i][j-1])){
        subAl.dSeq[k] = '-';
        subAl.qSeq[k] = qAlig[j-1];
        backtrackingLA(qlenght, table, dAlig, qAlig, subAl, k+1, i, j-1);
    }else{
        aux++;
    }
    
    if(table[i][j] == (table[i-1][j-1] + Rdq) && (table[i-1][j-1])){
        subAl.dSeq[k] = dAlig[i-1];
        subAl.qSeq[k] = qAlig[j-1];
        backtrackingLA(qlenght, table, dAlig, qAlig, subAl, k+1, i-1, j-1);
    }else{
        aux++;
    }
    
    if(aux==3){
        subAl.dSeq[k] = dAlig[i-1];
        subAl.qSeq[k] = qAlig[j-1];
        
        reverse_string(subAl.dSeq);
        reverse_string(subAl.qSeq);
        
        printf("\n>d: %s", subAl.dSeq);
        printf("\n>q: %s\n", subAl.qSeq);
    }
    return;
}

