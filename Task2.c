#include <stdio.h>
#include <string.h>
#include "trie.c"
#include <sys/time.h>

#define LINE_SIZE 2048


int main() {
    struct timeval t1, t2;
    double elapsedTime;

    gettimeofday(&t1, NULL);

    trieNode *root = NULL;
    char *fileNames [] = {"data1.txt", "data2.txt", "data3.txt", "data4.txt", "data5.txt", "data6.txt", "data7.txt", "data8.txt", "data9.txt", "data10.txt"};

    FILE *fp[10];
    FILE *out = fopen("dictionary2.txt", "w");
    for (int i = 0; i < 10; i++) {
        fp[i] = fopen(fileNames[i], "r");
        if (fp[i] == NULL) return -1;
    }

    for (int i = 0; i < 10 ; i++) {
        char inp[LINE_SIZE];
        while(fgets(inp, LINE_SIZE, fp[i]) ){
            if (inp[strlen(inp) - 1] == '\n') inp[strlen(inp) - 1] = '\0';
            char *token = strtok(inp, " ");
            while (token) {
                insertTrie(&root, token);
                token = strtok(NULL, " ");
            }
            memset(inp, 0, LINE_SIZE);
        }

        fclose(fp[i]);
    }
    print_trie(root, out);
    gettimeofday(&t2, NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;

    double time_taken = (elapsedTime) / 1000;
    printf("Main function took %lf seconds to execute.\n", time_taken);
    return 0;
}