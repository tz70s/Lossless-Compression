#include <stdio.h>
#include <stdlib.h>


void countLetters(FILE *input) {
    char c;
    int freqArray[27] = { 0 };

    while ((c=fgetc(input)) != EOF) {
        int loopCounter = 0;
        for( loopCounter = 0; loopCounter < 27; loopCounter++ ) {
            if ( loopCounter == (c-'a')) {
                freqArray[loopCounter]++;
            }
        }
        if (c == ' ') freqArray[26]++;
    }

    int i;
    for( i = 0; i<26; i++) {
        printf("%c : ", i+'a');
        printf("%d \n", freqArray[i]);
    }
    printf("  : %d\n",freqArray[26]);
}

int main(int argc, char *argv[]) {
    FILE *input, *output;
    
    input = fopen(argv[1], "r");
    countLetters(input);
    return 0;
}
