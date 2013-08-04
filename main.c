#include <stdio.h>
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
void print100(void); // Prints first 100 chars in array

bool amIBothered (unsigned char dave) {
    // Is the given unsigned character in the set of synt
    for (int i = 0; i < 8; i++) {
        if (dave == synt[i]) // Do I look bothered?
            return true; // Decidedly bothered
    }
    return false; // I ain't even bothered tho
}

void print100(void) {
    // For debug
    for (int i = 0; i < 100; i++) {
        printf("%d.", (int) data[i]);
    }
    printf("\n");
}

void process() {
    // Actyually processes the bf code
    unsigned char dave;
    dave = *iPointer;
    while (amIBothered(dave)) {
        //printf("Next instruction:%c, Data: %c\n", dave, *dataPointer); // Debug

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
                //printf("     Output: %c\n", *dataPointer); break;
                printf("%c", *dataPointer); break;
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
                if (*dataPointer != 0) {
                    // Jump back to [
                    while(*iPointer != '[')
                        iPointer--;
                } 
                break;

            default: // Should never happen, has been known to happen
                printf("\n\nDamn son, something broke. Tell me what you gone done. Here is dave: %c", dave);
                exit(EXIT_FAILURE);
        }
        iPointer++;
        dave = *iPointer;
    }
    //printf("Printing 100:\n");
    //print100();
    //printf("That's everything, finished\n");
}

int main(void) {
    // Main function
    data = (unsigned char * ) malloc(CellNo * sizeof(unsigned char));
    instructions = (unsigned char *) malloc(CellNo * sizeof(unsigned char));
    dataPointer = data;
    iPointer = instructions;
    if (NULL == data || NULL == instructions) {
        printf("Error allocating memory, please purchase a better potato.\n");
        exit(EXIT_FAILURE);
    }

    printf("Grade A Potato detected, please stand by.\n");
    printf("Spoolling up potato friends\n");
    printf("Type only the letter G to exit\n");
    printf("Please enter code now, ending in the letter G (all other letters apart from syntax will be ignored):\n");

    while (1) {

        for (int i = 0; i < CellNo; i++)
            // Fill up with 0's, as in spec
            data[i] = (unsigned char) 0, instructions[i] = (unsigned char) 0;

        // Get unsigned characters
        printf(">>> ");
        unsigned char next;
        scanf("%c", &next);
        if (next == 'G' || next == EOF)
            exit(EXIT_SUCCESS);

        iPointer = instructions;
        while (next != 'G' && next != EOF) {
            if (amIBothered(next)) {
                *iPointer = next;
                iPointer++;
            }
            scanf("%c", &next);
        }

        iPointer = instructions;
        //printf("Chunderific instructions: %s", iPointer); // For debug

        process();
    }

    printf("Program should not have gotten this far! Please report the bug with the input you used");
    exit(EXIT_FAILURE);

}
