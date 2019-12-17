#ifndef LOCALAL_H
#define LOCALAL_H

/*Macro Definitions*/
#ifndef LMATCH
    #define LMATCH 5
    #define LM_MATCH -3
    #define LGAP_PEN 5
    
    #define MAX_ALIGN 20
#endif

typedef struct Align Align;

/*DECLARATION OF FUNCTIONS*/
int localAlign(const char* dAlig, const char* qAlig, const int dlenght, const int qlenght);
struct Stack*  getScoreLA(const int dlenght, const int qlenght, int (*table)[qlenght], const char* dAlig, const char* qAlig);
void backtrackingLA(int qlenght, int (*table)[qlenght], const char* dAlig, const char* qAlig, Align subAl, int k, int i, int j);

#endif