#include <stdio.h>
#include <stdlib.h>

int freqArray[27] = { 0 };
int sortFreq[27] = { 0 };

struct node {
	int freq;
	char letter;
	struct node *lchild, *rchild;
};

typedef struct node Node;

void countLetters(FILE *input) {
    char c;

    while ((c=fgetc(input)) != EOF) {
        int loopCounter = 0;
        for( loopCounter = 0; loopCounter < 27; loopCounter++ ) {
            if ( loopCounter == (c-'a')) {
                freqArray[loopCounter]++;
            }
        }
        if (c == ' ') freqArray[26]++;
    }
}


void buildTree() {
	Node *temp;
	Node *arr[27];
	int i;
	for (i=0;i<27;i++) {
		arr[i] = malloc(sizeof(Node));
		arr[i]->freq = freqArray[i];
		arr[i]->letter = i;
		arr[i]->lchild = NULL;
		arr[i]->rchild = NULL;
	}
	
	for (i=0;i<26;i++) {
		printf("%c : ", arr[i]->letter + 'a');
		printf("%d \n", arr[i]->freq);
	}
	printf(" : %d \n", arr[26]->freq);
}

int main(int argc, char *argv[]) {
    FILE *input, *output;
	    
    input = fopen(argv[1], "r");
    countLetters(input);
	buildTree();
    return 0;
}
