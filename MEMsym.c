// Authors:
// Gracia de Vargas, Luis (INSG2A)
// Guerrero Fernández, Iván (INSG2A)
// Kleinschrot Colomer, Harald Xerxes (INSG2A)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TAM_LINEA 10
#define NUM_ROWS 7 // esto es un ejemplo, no se que poner

typedef struct {
    unsigned char ETQ;
    unsigned char Data[TAM_LINEA];
} T_CACHE_LINE;

void cleanCache(T_CACHE_LINE tbl[NUM_ROWS]) {} // end of cleanCache

void dumpCache(T_CACHE_LINE *tbl) {} // end of dumpCache

void parseAddress(unsigned int addr, int *LABEL, int *word, int *line, int *block) {} // end of parseAddress

void treatFailureMiss(T_CACHE_LINE *tbl, char *MRAM, int LABEL, int line, int block) {} // end of treatFailureMiss

int main() {
    printf("Al menos esto se está imprimiendo. \n");
    sleep(1);

    return 0;
} // end of main