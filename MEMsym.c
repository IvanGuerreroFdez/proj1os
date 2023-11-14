// Authors:
// Guerrero Fernández, Iván (INSG2A)
// Kleinschrot Colomer, Harald Xerxes (INSG2A)
// Gracia de Vargas, Luis (INSG2A)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TAM_LINEA 8
#define NUM_ROWS 7 // esto es un ejemplo, no se que poner

const int globalitme = 0;
const int numfallos = 0;

typedef struct {
    unsigned char ETQ;
    unsigned char Data[TAM_LINEA];
} T_CACHE_LINE;

// Counts no. of lines in a txt
int noLines(FILE *fp) {
    int cont = 0;
    char c;

    while(!feof(fp)) {
        if((c = getc(fp)) == '\n') {
            cont++;
        } // end if condition
    } // end while loop

    return cont;
} // end of noLines

// Reads a dynamic line of a file
char * leeLineDinamicaFichero(FILE * f) {
	char * linea = (char *) malloc(sizeof(char) * 3);
	int idx = 0;
	char c = 0;
	
    // Stores each character in linea
	do {
		//linea = (char*)realloc(linea,sizeof(char)*idx+1);
		c = getc(f);
		linea[idx] = c;
		idx++;

        // Reallocation of memory
        if((idx + 1) % 3 == 0) {
            linea = (char *) realloc(linea, sizeof(char) * (idx + 4));
        } // end if condition
	} while(!feof(f) && c != '\n'); // end do while
	
	if(c == '\n') { // Detects a change of line
		linea[idx-1] = '\0';
	} // end if condition

	return linea;
} // end of leeLineaDinamicaFichero

// Initializes the label fields to xFF (and cache data to x23)
void initialize(char * addr) {
    char addr = (char *) malloc(sizeof(char) * 3);

    for(int i = 0; i < sizeof(addr); i++) {
        while((char c = fgets()) != eof()) {
        // Descomponer en binario en palabra, linea y etiqueta/label

        } // end while loop
    } // end for loop
} // end of initialize

void cleanCache(T_CACHE_LINE tbl[NUM_ROWS]) {} // end of cleanCache

void dumpCache(T_CACHE_LINE *tbl) {} // end of dumpCache

void parseAddress(unsigned int addr, int *LABEL, int *word, int *line, int *block) {} // end of parseAddress

void treatFailureMiss(T_CACHE_LINE *tbl, char *MRAM, int LABEL, int line, int block) {} // end of treatFailureMiss

int main() {
    char *linea_buff;
    char *accesos = (char *) malloc(sizeof(char) * 10); // Array of memory accesses

    FILE *f = fopen("accesos_memoria.txt", "r");

    // This happens when the file is not found
    if(f == NULL) {
        printf("Could not open file.\n");
        return 1;
    } // end if condition
    
    for(int i = 0; i < noLines(f); i++) {
        linea_buff = leeLineDinamicaFichero(f);
        *(accesos + i) = linea_buff;

        if((i + 1) % 10 == 0) {
            accesos = (char *) realloc(accesos, sizeof(char) * (i + 11));
        } // end if condition
    } // end for loop
    
    initialize(linea_buff); // Invokes the function to initialize the label fields

    printf("Al menos esto se está imprimiendo. \n");
    sleep(1);

    fclose(f); // Closes the file
    return 0;
} // end of main