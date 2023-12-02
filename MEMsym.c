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

// Initializes the label fields to xFF and cache data to x23
void cleanCache(T_CACHE_LINE *tbl) {
    for(int i = 0; i < NUM_ROWS; i++) {
        tbl[i].ETQ = 0xFF;

        for(int j = 0; j < TAM_LINEA; j++) {
            tbl[i].Data[j] = 0x23;
        } // end for loop
    } // end for loop

} // end of cleanCache

// Function to display the contents of the cache
void dumpCache(T_CACHE_LINE *tbl) {
    for (int i = 0; i < NUM_ROWS; i++) {
        printf("ETQ: %02X, Data: ", tbl[i].ETQ);

        for (int j = 0; j < TAM_LINEA; j++) {
            printf("%02x ", tbl[i].Data[j]);
        } // end for loop

        printf("\n");
    } // end for loop
} // end of dumpCache

/*void parseAddress(unsigned int addr, int *LABEL, int *word, int *line, int *block) {
    *block = addr & 0x0F; // Extract the 4-bit block field
    *word = (addr >> 4) & 0x07; // Extract the 3-bit word field
    *line = (addr >> 7) & 0x07; // Extract the 3-bit line field
    *LABEL = (addr >> 10) & 0x1F; // Extract the 5-bit label field
} // end of parseAddress*/

void treatFailureMiss(T_CACHE_LINE *tbl, char *MRAM, int LABEL, int line, int block) {} // end of treatFailureMiss

int main() {
    // Initialization of variables
    char *linea_buff;
    FILE *memoryA = fopen("./accesos_memoria.txt", "r"); // Opens accesos_memoria.txt in read mode
    FILE *ramC = fopen("./CONTENTS_RAM.bin", "rb"); // Opens CONTENTS_RAM.bin in read mode
    FILE *cacheC = fopen("./CONTENTS_CACHE.bin", "wb"); // Opens CONTENTS_CACHE.bin in write mode
    T_CACHE_LINE *cacheConts = (T_CACHE_LINE *) malloc(NUM_ROWS * sizeof(T_CACHE_LINE)); // Array of cache lines, remember that NUM_ROWS = 8
    //unsigned char *simulRAM = (unsigned char *) malloc(sizeof(unsigned char) * 4096); // Array that reads the contents in CONTENTS_RAM.bin
    int *address = (int *) malloc(sizeof(int) * 5); // Array of division of address

    // Returns -1 when at least one of the files is not found
    if(memoryA == NULL) {
        printf("Could not open 'accesos_memoria.txt'. \n");
        return -1;
    } else if(ramC == NULL) {
        printf("Could not open 'CONTENTS_RAM.bin'. \n");
        return -1;
    } else if(cacheC == NULL) {
        printf("Could not open 'CONTENTS_CACHE.bin'. \n");
        return -1;
    } // end if, else if, else if conditions

    // Initializes cache contents
    cleanCache(cacheConts);

    // Dump the contents of the cache on the screen
    dumpCache(cacheConts);

    sleep(1); // 1 second sleep
    
    unsigned char *Simul_RAM = (unsigned char*) malloc(sizeof(unsigned char) * 4096);
    if (Simul_RAM == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return -1;
    } // end if condition

    fread(Simul_RAM, sizeof(unsigned char), 4096, ramC);

    /*//PRUEBA
    for (int i=0; i<linesInMemoryA; i++) {
        printf("%02X \n", Simul_RAM[i]);
    }
    printf("\n");*/ 

    // address[0] = linea i de accesos memoria;
    //parseAddress(address[0], address[1], address[2], address[3], address[4]); // address[1-4] are empty and ready to be substituted
    
    /*
    //Print Miss or Hit
    printf("T: %d, Cache Miss %d, Address %04X, Label %X, Line %02X, Word %02X, Block %02X", i++, failNo++, addr, *LABEL, *line, *word, *block);
    printf("T: %d, Cache Hit, Address %04X, Label %X, Line %02X, Word %02X, Data %02X", i++, addr, *LABEL, *line, *word, <ALGO>);
    */
   
    // Calculates the cache line of a given address


    // Checks if tag cache line contains is the same


    // Writes the number of accesses and failures, avg time and text read


    // Process ends after reading dirs_memoria.txt (accesos_memoria.txt???) and actions needed


    // Dump contents of information into CONTENTS_CACHE.bin


    // Closes the files
    fclose(memoryA);
    fclose(ramC);
    fclose(cacheC);

    // Frees dynamic memory allocations
    free(linea_buff);
    free(cacheConts);
    free(Simul_RAM);

    printf("Al menos esto se esta imprimiendo. \n");

    return 0;
} // end of main