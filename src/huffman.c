#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int freqArray[27] = { 0 };
typedef struct node {
	int freq;
	char letter;
	struct node *lchild, *rchild;
} Node;

Node arr[27];
int maxFreq = 0;
int coArr[27] = { 0 };

/* 
=============================

Count the frequencies of letters

=============================
*/

void countLetters(FILE *input) {
    char c;

    while ((c=fgetc(input)) != EOF) {
        int loopCounter = 0;
        for( loopCounter = 0; loopCounter < 27; loopCounter++ ) {
            if ( loopCounter == (c-'a')) {
                freqArray[loopCounter]++;
				maxFreq++;
            }
        }
        if (c == ' ') {
			freqArray[26]++;
			maxFreq++;
		}
    }
}

void buildTree() {
	int i;
	for (i = 0; i < 27; i++ ) {
		arr[i].freq = freqArray[i];
		arr[i].letter = i;
		arr[i].lchild = NULL;
		arr[i].rchild = NULL;

	}
}

/* 
===========================

Sort tree

===========================
*/

void InsertionSort(Node* pNodes, int num) {
	
	if( NULL == pNodes || num < 0 ) return;

	int i, j;
	for( i = 1; i < num; i++ ) {
		Node pivot = pNodes[i];
		for( j = i - 1; j >= 0; j-- ) {
			if( pivot.freq < pNodes[j].freq ) {
				pNodes[j+1] = pNodes[j];
			} else {
				break;
			}
		}
		if( pivot.freq < pNodes[j+1].freq ) {
			pNodes[j+1] = pivot;
		}
	}
}

/* 
==========================

Huffman Tree

==========================
*/

void prefix(Node* pNode ,int code) {
	if(NULL == pNode) return;
	if(pNode && (pNode->lchild == NULL) && (pNode->rchild == NULL) ) {
		if(pNode->freq != 0) {
			coArr[(int)pNode->letter] = code;
		}
		return;
	}
	prefix(pNode->lchild , code *10 + 2);
	prefix(pNode->rchild , code *10 + 1);
}

void prefix_free(Node* pNode) {
	if(NULL == pNode) return;
	if(pNode && (pNode->lchild == NULL) && (pNode->rchild == NULL) ) {
		free(pNode);
		return;
	}
	prefix_free(pNode->lchild);
	prefix_free(pNode->rchild);
	free(pNode);
}

Node* BuildHuffmanTree(Node* pData, int num) {
	
	int remain = num;
	int index = 0;
	
	Node* pRoot = NULL;
	Node* pLeft = NULL;
	Node* pRight = NULL;
	
	while( remain > 1) {

		InsertionSort(&arr[index], remain);
		pRoot = (Node*)calloc(1, sizeof(Node));
		pLeft = (Node*)calloc(1, sizeof(Node));
		pRight = (Node*)calloc(1, sizeof(Node));

		if( pRoot && pLeft && pRight) {
			*pLeft = arr[index];
			*pRight = arr[index+1];
			pRoot->letter = '\0';
			pRoot->freq = pLeft->freq + pRight->freq;
			pRoot->lchild = pLeft;
			pRoot->rchild = pRight;
			arr[index+1] = *pRoot;
		}  
		index++;
		remain -= 1;
	}

	return pRoot;
}


/*
============================

Compression

============================
*/
void Compression(FILE *input) {
	char c;
	uint16_t numarr[100] = {0};
	int index = 0;
	int shift = 0;

	while ((c=fgetc(input)) != EOF) {
        int loopCounter = 0;
        for( loopCounter = 0; loopCounter < 27; loopCounter++ ) {
            if ( loopCounter == (c-'a')) {
            	printf("%d",coArr[loopCounter]);
            	int temp = coArr[loopCounter];
            	while(temp != 0) {
            		int x = temp % 10 - 1;
            		temp = temp / 10;
            		numarr[index] |= x;
            		numarr[index] <<= 1;
            		shift++;
            		if(shift == 15) {
            			index++;
            			shift = 0;
            		}
            	}
            	
            }

        }
    }

    printf("\n\n%u\n",numarr[0]);

    for(index = 0; index < 100; index++) {
    	if(numarr[index] == 0) {
    		break;
    	} else {
    		printf("%u",numarr[index]);
    	}
    }
}

int main(int argc, char *argv[]) {
    FILE *counter,*input, *output;
	
	char *s = argv[1];
    counter = fopen(s, "r");

    countLetters(counter);
    fclose(counter);
    buildTree();
    /*
    int i = 0;
    for (; i < 27; i++) {
    	printf("%c : ", arr[i].letter + 'a');
    	printf("%d\n", arr[i].freq);
    }
    */
    InsertionSort(&arr[0],27);
    /*
    i = 0;
    for (; i < 27; i++) {
    	printf("%c : ", arr[i].letter + 'a');
    	printf("%d\n", arr[i].freq);
    }
    */
    Node* pRoot = BuildHuffmanTree(arr,27);
    printf("%d\n",pRoot->freq);
    int code = 0;
 	prefix(pRoot, code);
 	int i = 0;
 	for(; i<27; i++) {
 		printf("%c : ",i+'a');
 		printf("%d\n",coArr[i]);
 	}

 	input = fopen(s, "r");
 	Compression(input);
 	printf("\n");

    return 0;
}
