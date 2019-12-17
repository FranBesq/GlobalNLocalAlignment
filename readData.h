
#ifndef READDATA_H
#define READDATA_H

/*DECLARATION OF FUNCTIONS*/
int readFASTA(const char *fileName, char * string, int lenght);
int getFASTALenght(const char * fileName);
void printTable(int dlenght, int qlenght, int (*table)[qlenght], const char* dAlig, const char* qAlig);
void reverse_string(char *str);

#endif