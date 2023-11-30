// Authors:
// Gracia de Vargas, Luis (INSG2A)
// Guerrero Fernández, Iván (INSG2A)
// Kleinschrot Colomer, Harald Xerxes (INSG2A)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TAM_LINEA 16
#define NUM_ROWS 8

float avgTime = 0;
int failNo = 0;

// Struct for cache lines
typedef struct {
    unsigned char ETQ;
    unsigned char Data[TAM_LINEA];
} T_CACHE_LINE;

// Counts no. of lines in a file
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
char * leeLineDinamicaFichero(FILE *f) {
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
void initialize(char *addr, FILE *f) {
    char c;
    addr = (char *) malloc(sizeof(char) * 3); 

    for(int i = 0; i < sizeof(addr); i++) {
        while(c = getchar() != feof(f)) {
        // Descomponer en binario en palabra, linea y etiqueta/label

        } // end while loop
    } // end for loop
} // end of initialize

void cleanCache(T_CACHE_LINE tbl[NUM_ROWS]) {} // end of cleanCache

void dumpCache(T_CACHE_LINE *tbl) {} // end of dumpCache

void parseAddress(unsigned int addr, int *LABEL, int *word, int *line, int *block) {} // end of parseAddress

void treatFailureMiss(T_CACHE_LINE *tbl, char *MRAM, int LABEL, int line, int block) {} // end of treatFailureMiss

int main() {
    // Initialization of variables
    char *linea_buff;
    char *accesos = (char *) malloc(sizeof(char) * 10); // Array of memory accesses
    FILE *memoryA = fopen("accesos_memoria.txt", "r"); // Opens accesos_memoria.txt in read mode
    FILE *ramC = fopen("CONTENTS_RAM.bin", "r"); // Opens CONTENTS_RAM.bin in read mode
    T_CACHE_LINE *cacheConts = (T_CACHE_LINE *) malloc(NUM_ROWS * sizeof(T_CACHE_LINE)); // Array of cache lines, remember that NUM_ROWS = 8

    // Returns -1 when at least one of the files is not found
    if(memoryA == NULL) {
        printf("Could not open 'accesos_memoria.txt'. \n");
        return -1;
    } else if(ramC == NULL) {
        printf("Could not open 'CONTENTS_RAM.bin'. \n");
        return -1;
    } // end if, else if conditions
    
    for(int i = 0; i < noLines(memoryA); i++) {
        linea_buff = leeLineDinamicaFichero(memoryA);
        *(accesos + i) = linea_buff;

        if((i + 1) % 10 == 0) {
            accesos = (char *) realloc(accesos, sizeof(char) * (i + 11));
        } // end if condition
    } // end for loop
    
    initialize(linea_buff, memoryA); // Invokes the function to initialize the label fields

    // Dump the contents of the cache on the screen


    // Calculates the cache line of a given address


    // Checks if tag cache line contains is the same


    sleep(1); // 1 second sleep

    // Writes the number of accesses and failures, avg time and text read


    // Process ends after reading dirs_memoria.txt (accesos_memoria.txt???) and actions needed

    printf("Al menos esto se está imprimiendo. \n");

    // Closes the files
    fclose(memoryA);
    fclose(ramC);

    return 0;
} // end of main