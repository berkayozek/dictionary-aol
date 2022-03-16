#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "trie.c"



int main() {
    trieNode *root = createNode('\0');
    char *fileNames[] = {"data1.txt", "data2.txt", "data3.txt", "data4.txt", "data5.txt", "data6.txt", "data7.txt",
                         "data8.txt", "data9.txt", "data10.txt"};
    struct timeval t1, t2;
    double elapsedTime;

    gettimeofday(&t1, NULL);

    FILE *fp[10];
    FILE *outFp = fopen("dictionary6.txt", "w");
    for (int i = 0; i < 10; i++) {
        fp[i] = fopen(fileNames[i], "r");
        if (fp[i] == NULL || root == NULL) return -1;
    }
    for (int i = 0; i < 10; i++) {
        fseek(fp[i], 0, SEEK_END);
        long fsize = ftell(fp[i]);
        fseek(fp[i], 0, SEEK_SET);  /* same as rewind(f); */

        char* string = malloc(fsize + 1);
        fread(string, 1, fsize, fp[i]);
        fclose(fp[i]);
        string[fsize] = 0;

        char* endTokenLine = NULL;
        char* lineToken = strtok_r(string, "\n", &endTokenLine);

        while(lineToken != NULL) {
            char* endTokenTerm = NULL;
            char* termToken = strtok_r(lineToken, " ", &endTokenTerm);
            while (termToken) {
                insertTrie(&root, termToken);
                termToken = strtok_r(NULL, " ", &endTokenTerm);
            }
            lineToken = strtok_r(NULL, "\n", &endTokenLine);
        }
        free(string);
    }

    print_trie(root, outFp);
    gettimeofday(&t2, NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;

    double time_taken = (elapsedTime) / 1000;
    printf("Main function took %lf seconds to execute.\n", time_taken);
    fclose(outFp);
    return 0;
}