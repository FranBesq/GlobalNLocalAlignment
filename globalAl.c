// Affine scoring scheme
//  match:    10
//  mismatch: 0
//  gap:      10 + 1 * (l - 1)

#include "globalAl.h"
#include "readData.h"
#include <stdlib.h>	
#include <string.h>
#include <stdio.h>

int globalAlign(const char* dAlig, const char* qAlig, const int dlenght, const int qlenght){
    
    /*We create the tables required for DP*/
    int tableE[dlenght][qlenght];
    int tableF[dlenght][qlenght];
    int tableG[dlenght][qlenght];
    
    int i, j;/*Counters used to go throw the tables*/
    
    /*Initialization of the first row and column*/
    tableE[0][0] = 0;
    tableF[0][0] = 0;
    tableG[0][0] = 0;
    
    for(j=1;j< qlenght; j++){
        tableE[0][j] = (-GAP_OPEN) -j + 1;
        tableF[0][j] = (-GAP_OPEN) -j + 1; 
        tableG[0][j] = (-GAP_OPEN) -j + 1; 
    }
    for(i=1;i < dlenght; i++){
        tableE[i][0] = (-GAP_OPEN) -i + 1;
        tableF[i][0] = (-GAP_OPEN) -i + 1; 
        tableG[i][0] = (-GAP_OPEN) -i + 1; 
    }
    
    return getScore(dlenght, qlenght, tableE, tableF, tableG, dAlig, qAlig);
}

/*Main function that goes throw the tables and gets the optimal score*/
int getScore(const int dlenght, const int qlenght, int (*tableE)[qlenght], int (*tableF)[qlenght], int (*tableG)[qlenght], const char* dAlig, const char* qAlig){
    
    int i, j;

    for (i = 1; i < dlenght; i++) {
        
        for (j = 1; j < qlenght; j++) {
            updateTableE(qlenght, tableE, tableF, tableG, i, j);//No se pasa el & right??
            updateTableF(qlenght, tableE, tableF, tableG, i, j);
            updateTableG(qlenght, tableE, tableF, tableG, i, j, dAlig, qAlig);
        }
        
    }
    
    printf("==Global Alignment==\n");
    printf("\nTable E\n");
    printTable(dlenght, qlenght, tableE, dAlig, qAlig);
    printf("\n\nTable F\n");
    printTable(dlenght, qlenght, tableF, dAlig, qAlig);
    printf("\n\nTable G\n");
    printTable(dlenght, qlenght, tableG, dAlig, qAlig);
    
    return maxScore(qlenght, tableE, tableF, tableG, dlenght - 1, qlenght - 1);
}

void updateTableE(int qlenght, int (*tableE)[qlenght], int (*tableF)[qlenght], int (*tableG)[qlenght], int i, int j){
    //Control de errores ?
    
    int max;
    int newE;
    int newF = tableF[i-1][j] - GAP_OPEN;
    int newG = tableG[i-1][j] - GAP_OPEN;
    /*In case we are on the second row we need to manage the exception*/
    newE = (i == 1) ? tableE[i-1][j] - GAP_OPEN : tableE[i-1][j] - GAP_EXTEND; 
    
    /*Position [i][j] is updated with the optimal score*/
    max = newE > newF ? newE : newF;
    tableE[i][j] = max > newG ? max : newG;

}

void updateTableF(int qlenght, int (*tableE)[qlenght], int (*tableF)[qlenght], int (*tableG)[qlenght], int i, int j){
    //Control de errores ?
    
    int max ;
    int newF;
    int newE = tableE[i][j-1] - GAP_OPEN;
    int newG = tableG[i][j-1] - GAP_OPEN;
    /*In case we are on the second row we need to manage the exception*/
    newF = j != 1 ? tableF[i][j-1] - GAP_EXTEND : tableF[i][j-1] - GAP_OPEN; 
    
    /*Position [i][j] is updated with the optimal score*/
    max = newF > newE ? newF : newE;
    tableF[i][j] = max > newG ? max : newG;
    
}

void updateTableG(int qlenght, int (*tableE)[qlenght], int (*tableF)[qlenght], int (*tableG)[qlenght], int i, int j, const char* dAlig, const char* qAlig){
        //Control de errores ?
        
    int Rdq;
    int max;
    /*Is there a match or mismatch?*/
    Rdq = dAlig[i-1] == qAlig[j-1] ? MATCH : M_MATCH; //es -1 porque i y j empiezan el 1
    
    int newG = tableG[i-1][j-1] + Rdq;
    int newE = tableE[i-1][j-1] + Rdq;
    int newF = tableF[i-1][j-1] + Rdq;
    
    /*Position [i][j] is updated with the optimal score*/
    max = newG > newE ? newG : newE;
    tableG[i][j] = max > newF ? max : newF;

}

/*Returns the maximum score of a certain position*/
int maxScore(int qlenght, int (*tableE)[qlenght], int (*tableF)[qlenght], int (*tableG)[qlenght], int i, int j){
    
    int max = tableG[i][j];
    
    /*Position [i][j] is updated with the optimal score*/
    max =  max > tableF[i][j] ? max : tableF[i][j];
    max =  max > tableE[i][j] ? max : tableE[i][j];
    
    return max;
}