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

void parseAddress(unsigned int addr, int *LABEL, int *word, int *line, int *block) {
    *block = addr & 0x0F; // Extract the 4-bit block field
    *word = (addr >> 4) & 0x07; // Extract the 3-bit word field
    *line = (addr >> 7) & 0x07; // Extract the 3-bit line field
    *LABEL = (addr >> 10) & 0x1F; // Extract the 5-bit label field
} // end of parseAddress

void treatFailureMiss(T_CACHE_LINE *tbl, char *MRAM, int LABEL, int line, int block) {
        // Copy the corresponding block from the MRAM array
        int startAddress = (block << 7) | (line << 4);
        memcpy(tbl[line].Data, &MRAM[startAddress], TAM_LINEA);
        // Update the Label field
        tbl[line].ETQ = LABEL;
} // end of treatFailureMiss

int main() {
    // Initialization of variables
    int failNo = 0;
    FILE *memoryA = fopen("./accesos_memoria.txt", "r"); // Opens accesos_memoria.txt in read mode
    FILE *ramC = fopen("./CONTENTS_RAM.bin", "rb"); // Opens CONTENTS_RAM.bin in read mode
    FILE *cacheC = fopen("./CONTENTS_CACHE.bin", "wb"); // Opens CONTENTS_CACHE.bin in write mode
    T_CACHE_LINE *cacheConts = (T_CACHE_LINE *) malloc(NUM_ROWS * sizeof(T_CACHE_LINE)); // Array of cache lines, remember that NUM_ROWS = 8
    unsigned char *simulRAM = (unsigned char *) malloc(sizeof(unsigned char) * 4096); // Array that reads the contents in CONTENTS_RAM.bin
    int *address = (int *) malloc(sizeof(int) * 5); // Array of division of address
    char *text = (char *)malloc(sizeof(char) * 16); // Dynamic memory for text
    int textIndex = 0;

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
    
    unsigned char *Simul_RAM = (unsigned char*) malloc(sizeof(unsigned char) * 4096);
    if (Simul_RAM == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return -1;
    } // end if condition

    fread(Simul_RAM, sizeof(unsigned char), 4096, ramC); // Read the content of CONTENTS_RAM and stores it on Simul_RAM 
    /*//PRUEBA
    for (int i=0; i<linesInMemoryA; i++) {
        printf("%02X \n", Simul_RAM[i]);
    }
    printf("\n");*/ 

    rewind(memoryA);
    char *linea_buff = (char *) malloc(sizeof(char) * 16);
    int globalTime = 0;
    int accesses = 0;
    while (fgets(linea_buff, 16, memoryA) != NULL) { //16 is used instead of sizeof(linea_buff) to return the allocated size for the buffer
        unsigned int address = strtoul(linea_buff, NULL, 16);
        int LABEL, word, line, block;
        parseAddress(address, &LABEL, &word, &line, &block);

        if(LABEL == cacheConts[line].ETQ) {
            printf("T: %d, Cache Hit, Address %04X, Label %X, Line %02X, Word %02X, Data %02X\n", globalTime, address, LABEL, line, word, cacheConts[line].Data[word]); 
            globalTime++;

            // Dump the contents of the cache on the screen
            dumpCache(cacheConts);

            text[textIndex] = cacheConts[line].Data[word];
            textIndex++;
            if(textIndex % 16 == 0) {
                text = realloc(text, sizeof(char) * (16 + textIndex));
            } // end if condition*
        } else {
            printf("T: %d, CACHE Fault %d, ADDR %04X Label %X line %02X word %02X block %02X\n", globalTime, failNo++, address, LABEL, line, word, block);
            globalTime += 20;
            
            //cache miss handler
            treatFailureMiss(cacheConts, Simul_RAM, LABEL, line , block);

            // Print a message indicating the block X is being loaded in the line Y
            printf("Loading Block %02X into Line %02X\n", block, line);
        } // end if else condition

        accesses++;
        sleep(1); // 1 second sleep
    } // end while loop

    // Writes the number of accesses and failures, avg time and text read
    printf("Total accesses: %d; faults: %d; Average time: %.2f\n", accesses, failNo, (float)globalTime / accesses);
    printf("Text read: ");
    for (int i = 0; i < textIndex; i++) {
        printf("%c", text[i]);
    } // end for loop

    printf("\n");

    // Dump contents of information into CONTENTS_CACHE.bin
    for(int i = 0; i < NUM_ROWS; i++) {
        for(int j = 0; j < TAM_LINEA; j++) {
            fprintf(cacheC, "%x ", cacheConts[i].Data[j]);
        } // end for loop

        fprintf(cacheC, "\n");
    } // end for loop

    // Closes the files
    fclose(memoryA);
    fclose(ramC);
    fclose(cacheC);

    // Frees dynamic memory allocations
    free(linea_buff);
    free(cacheConts);
    free(Simul_RAM);
    free(text);

    printf("Al menos esto se esta imprimiendo. \n");

    return 0;
} // end of main