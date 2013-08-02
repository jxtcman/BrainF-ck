#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#define CellNo 30001

unsigned char synt[] = {'>', '<', '+', '-', '.', ',', '[', ']'};
unsigned char * data; // If this isn't one byte on your system, buy new potato with one byte  char
unsigned char * dataPointer;
unsigned char * instructions;
unsigned char * iPointer; // Points to instructions

void process(void);
bool amIBothered(unsigned char);

bool amIBothered (unsigned char dave) {
    // Is the given unsigned character in the set of synt
    for (int i = 0; i < 8; i++) {
        if (dave == synt[i]) // Do I look bothered?
            return true; // Decidedly bothered
    }
    return false; // I ain't even bothered tho
}

void process() {
    // Actyually processes the bf code
    unsigned char dave;
    do {
        dave = *iPointer;
        printf("Next instruction:%c\n", dave);

        switch (dave) {
            case '>':
                dataPointer++; break;
            case '<':
                dataPointer--; break;
            case '+':
                ++ *dataPointer; break;
            case '-':
                -- *dataPointer; break;
            case '.':
                printf("        Output: %c\n", *dataPointer); break;
            case ',':
                *dataPointer = getchar(); break;
            case '[':
                if (*dataPointer == 0) {
                    // jump to after next ]
                    while (*iPointer != ']')
                        iPointer++;
                }
                break;
            case ']':
                if (*dataPointer != '0') {
                    // Jump back to [
                    while(*iPointer != '[')
                        iPointer--;
                } 
            break;

            default:
                printf("\n\nDamn son, something broke. Tell me what you gone done. Here is dave: %c", dave);
                exit(EXIT_FAILURE);
        }
        iPointer++;
    } while (amIBothered(dave));
    printf("That's everything, finished\n");
}

int main(void) {
    // Main function
    data = (unsigned char * ) malloc(CellNo * sizeof(unsigned char));
    instructions = (unsigned char *) malloc(10000 * sizeof(unsigned char));
    dataPointer = data;
    iPointer = instructions;
    if (NULL == data || NULL == instructions) {
        printf("Error allocating memory, please purchase a better potato.\n");
        exit(EXIT_FAILURE);
    }

    printf("Grade A Potato detected, please stand by.\n");
    printf("Spoolling up potato friends\n");

    for (int i = 0; i < CellNo; i++)
        // Fill up with 0's, as in spec
        data[i] = (unsigned char) 0;

    printf("Please enter code now, ending in an G unsigned character:\n");

    // Get unsigned characters
    unsigned char next;
    while (scanf("%c", &next) & next != 'G') {
        if (amIBothered(next)) {
            *iPointer = next;
            iPointer++;
        }
    }

    iPointer = instructions;
    printf("Chunderific instructions: %s", iPointer);

    process();
    exit(0);

}
