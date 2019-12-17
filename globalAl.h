#ifndef GLOBALAL_H
#define GLOBALAL_H

/*Macros Definitions*/
#ifndef MATCH
    #define MATCH 10
    #define M_MATCH 0
    #define GAP_OPEN 10
    #define GAP_EXTEND 1
#endif

/*DECLARATION OF FUNCTIONS*/
int globalAlign(const char* dAlig, const char* qAlig, const int dlenght, const int qlenght);
int getScore(const int dlenght, const int qlenght, int (*tableE)[qlenght], int (*tableF)[qlenght], int (*tableG)[qlenght], const char* dAlig, const char* qAlig);
void updateTableE(int qlenght, int (*tableE)[qlenght], int (*tableF)[qlenght], int (*tableG)[qlenght], int i, int j);
void updateTableF(int qlenght, int (*tableE)[qlenght], int (*tableF)[qlenght], int (*tableG)[qlenght], int i, int j);
void updateTableG(int qlenght, int (*tableE)[qlenght], int (*tableF)[qlenght], int (*tableG)[qlenght], int i, int j, const char* dAlig, const char* qAlig);
int maxScore(int qlenght, int (*tableE)[qlenght], int (*tableF)[qlenght], int (*tableG)[qlenght], int i, int j);

#endif