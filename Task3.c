#include <stdio.h>
#include <string.h>
#include "trie.c"
#include <sys/time.h>

#define LINE_SIZE 2048

int main() {
    struct timeval t1, t2;
    double elapsedTime;

    gettimeofday(&t1, NULL);

    trieNode *root = createNode('\0');
    char fileNames[10][20] = {{"data1.txt"}, {"data2.txt"}, {"data3.txt"},
                              {"data4.txt"}, {"data5.txt"}, {"data6.txt"},
                              {"data7.txt"}, {"data8.txt"}, {"data9.txt"},
                              {"data10.txt"}};

    FILE *out = fopen("dictionary3.txt", "w");
    FILE *fp[10];
    for (int i = 0; i < 10; i++) {
        fp[i] = fopen(fileNames[i], "r");
        if (fp[i] == NULL || root == NULL) return -1;
    }

    for (int i = 0; i < 10 ; i++) {
        char inp[LINE_SIZE];
        size_t size = LINE_SIZE;

        fseek(fp[i], 0, SEEK_END);
        unsigned long fileSize = ftell(fp[i]);
        rewind(fp[i]);

        while (fileSize > 0) {
            memset(inp, 0, size);
            if (fileSize < size) size = fileSize;
            fread(inp, size, 1, fp[i]);

            char *inp2 = (char *) malloc(LINE_SIZE * sizeof (char));
            strcpy(inp2, inp);
            char *queryEndToken;
            char *token = strtok_r(inp2, "\n", &queryEndToken);
            int deletedSize = 0;
            while (token != NULL) {
                long currentIndex = token - inp2;
                int isEnd = 0;

                for (int j=currentIndex; inp[currentIndex] && j < LINE_SIZE; j++)
                    if (inp[j] == '\n'){
                        isEnd = 1;
                        break;
                    }

                if (isEnd == 0 && LINE_SIZE < fileSize) {
                    fseek(fp[i], currentIndex - strlen(inp), SEEK_CUR);
                    deletedSize = (currentIndex - strlen(inp));
                    break;
                }
                char *termsEndToken;
                char *terms = strtok_r(token, " ", &termsEndToken);
                while (terms != NULL) {
                    insertTrie(&root, terms);
                    terms = strtok_r(NULL, " ", &termsEndToken);
                }

                token = strtok_r(NULL, "\n", &queryEndToken);
            }


            //printf("%s", inp);
            fileSize -= size + deletedSize;
            free(inp2);
            inp2 = NULL;
        }
        fclose(fp[i]);
    }
    print_trie(root, out);
    gettimeofday(&t2, NULL);
    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;
    double time_taken = (double ) elapsedTime / 1000;

    printf("Main function took %lf seconds to execute.\n", time_taken);
    fclose(out);
    return 0;
}