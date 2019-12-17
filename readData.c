#include "readData.h"
#include <stdlib.h>	
#include <string.h>
#include <stdio.h>

/*reads fileName and resturns a string with the alignment
*
*Does not validate if it is fasta format
*/
int readFASTA(const char *fileName, char * string, int lenght){
    
    if(!fileName)return 0;//definir el error como -1
    
    FILE *f;
    int i;
    char c;

    f = fopen(fileName, "r");
    
    if(!f)return 0;

    for(i = 0;(c = getc(f)), i < (lenght + 3); i++){
        /*We ignore the first 3 characters of the file */
        if(i>2){/*We add the FASTA file to our string*/
            string[i-3] = c;
        }
    }
    return 1;
}

/*Returns the lenght of an alignmet read in FASTA*/
int getFASTALenght(const char* fileName){
    
    int i;
    char c;
    FILE *f = fopen(fileName, "r");
    
    if(!f)return -1;
    
    for(i = 0;(c = getc(f)) != EOF; i++);
    
    return i-4;/*OJITO CON ESTO, NO SE SI ES -1 O COMO*/
}

void printTable(int dlenght, int qlenght, int (*table)[qlenght], const char* dAlig, const char* qAlig){
    
    int i, j;
    
    printf("---------------------\n");
    
    for (i = 0; i < (dlenght -1); i++){
        if(!i) printf("         ");
        printf("   %c ", qAlig[i]);
    }
    for (i = 0; i < dlenght; i++) {
        
        printf("\n-- ");
        if(i != 0) printf("%c  ", dAlig[i-1]);
        else printf("   ");
        for (j = 0; j < qlenght; j++) {
            printf("|%d|",table[i][j]);
        }
        
        printf("--\n");
    }
}

//function from https://stackoverflow.com/questions/784417/reversing-a-string-in-c
void reverse_string(char *str)
{
    /* get range */
    char *start = str;
    char *end = start + strlen(str) - 1; /* -1 for \0 */
    char temp;

    /* reverse */
    while (end > start)
    {
        /* swap */
        temp = *start;
        *start = *end;
        *end = temp;

        /* move */
        ++start;
        --end;
    }
}