#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>
#include "trie.c"

#define LINE_SIZE 1024

pthread_t tid[10];
pthread_mutex_t lock;
trieNode *root;
FILE *fp[10];

void *readFile(void *param);

int main() {
    struct timeval t1, t2;
    double elapsedTime;

    gettimeofday(&t1, NULL);
    root = createNode('\0');
    char *fileNames [] = {"data1.txt", "data2.txt", "data3.txt", "data4.txt", "data5.txt", "data6.txt", "data7.txt", "data8.txt", "data9.txt", "data10.txt"};

    FILE *outFp = fopen("dictionary4.txt", "w");
    for (int i = 0; i < 10; i++) {
        fp[i] = fopen(fileNames[i], "r");
        if (fp[i] == NULL || root == NULL || outFp == NULL) return -1;
    }
    for (int i=0; i<10; i++) {
        pthread_create(&tid[i], NULL, (void *)readFile, fp[i]);
    }

    for(int i=0; i<10; i++){
        pthread_join(tid[i], NULL);
    }
    print_trie(root, outFp);
    gettimeofday(&t2, NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;

    double time_taken = (elapsedTime) / 1000;

    printf("Main function took %lf seconds to execute.\n", time_taken);
    return 0;
}

void *readFile(void *param){
    FILE *innerFp = (FILE *) param;
    char inp[LINE_SIZE];
    while(fgets(inp, LINE_SIZE, innerFp) ){
        if (inp[strlen(inp) - 1] == '\n') inp[strlen(inp) - 1] = '\0';
        char *endPointer;
        char *token = strtok_r(inp, " ", &endPointer);
        while (token) {

            pthread_mutex_lock(&lock);
            insertTrie(&root, token);
            pthread_mutex_unlock(&lock);
            token = strtok_r(NULL, " ", &endPointer);
        }

        memset(inp, 0, LINE_SIZE);
    }

    fclose(innerFp);
}
