#include <stdio.h>
#include <string.h>
#include "trie.c"
#include <pthread.h>
#include <sys/time.h>

pthread_t tid[10];
trieNode *roots[10];
FILE *fp[10];
pthread_mutex_t lock;
int numbers[] = {0,1,2,3,4,5,6,7,8,9};

#define LINE_SIZE 1024

void *readFile(void *);
void merge(trieNode **parentRoot, trieNode *childRoot,  char *word, int depth);

int main() {
    struct timeval t1, t2;
    double elapsedTime;

    gettimeofday(&t1, NULL);

    char *fileNames[] = {"data1.txt", "data2.txt", "data3.txt", "data4.txt", "data5.txt", "data6.txt", "data7.txt",
                         "data8.txt", "data9.txt", "data10.txt"};

    FILE *outFp = fopen("dictionary5.txt", "w");
    for (int i = 0; i < 10; i++) {
        fp[i] = fopen(fileNames[i], "r");
        roots[i] = createNode('\0');
        if (fp[i] == NULL) return -1;
    }
    for (int i=0; i<10; i++) {
        pthread_create(&tid[i], NULL, (void *)readFile, &numbers[i]);
    }

    for(int i=0; i<10; i++){
        pthread_join(tid[i], NULL);
    }


    for (int i = 1; i < 10; ++i) {
        char word[LINE_SIZE];
        merge(&roots[0], roots[i], word, 0);
    }

    print_trie( roots[0], outFp);

    gettimeofday(&t2, NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;

    double time_taken = (elapsedTime) / 1000;
    printf("Main function took %lf seconds to execute.\n", time_taken);

    for (int i = 0; i < 10; ++i) {
        deleteTrie((roots+i));
    }

    fclose(outFp);
    return 0;
}

void *readFile(void *param){
    int index = *((int *) (param));
    FILE *innerFp = fp[index];
    char inp[LINE_SIZE];
    while(fgets(inp, LINE_SIZE, innerFp) ){
        if (inp[strlen(inp) - 1] == '\n') inp[strlen(inp) - 1] = '\0';
        char *endToken;
        char *token = strtok_r(inp, " ",&endToken);
        while (token) {
            insertTrie((roots + index), token);
            token = strtok_r(NULL, " ", &endToken);
        }
        memset(inp, 0, LINE_SIZE);
    }

    fclose(innerFp);
}

void merge(trieNode **parentRoot, trieNode *childRoot,  char *word, int depth){
    if (!parentRoot || !childRoot)
        return;

    trieNode *temp = childRoot;

    merge(parentRoot, temp->left, word, depth);

    word[depth] = temp->data;

    if (temp->isLeaf){
        word[depth + 1] = '\0';
        insertTrieCount(parentRoot, word, temp->count);
    }

    merge(parentRoot, temp->eq, word, depth + 1);


    merge(parentRoot, temp->right, word, depth);
}
