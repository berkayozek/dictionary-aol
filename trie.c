#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "trie.h"
#define MAX 1024

trieNode* createNode(char data){
    trieNode *newNode = (trieNode *) malloc(sizeof(trieNode ));
    newNode->data = data;
    newNode->left = newNode->eq = newNode->right = 0;
    newNode->isLeaf = 0;
    newNode->count = 0;
    return newNode;
}

void insertTrie(trieNode **root, char *word) {
    if (!(*root))
        *root = createNode(*word);

    if ((*word) < (*root)->data)
        insertTrie(&( (*root)->left ), word);
    else if ((*word) > (*root)->data)
        insertTrie(&( (*root)->right ), word);
    else
    {
        if (*(word+1))
            insertTrie(&( (*root)->eq ), word+1);
        else{
            (*root)->count++;
            (*root)->isLeaf = 1;
        }
    }
}

void insertTrieCount(trieNode **root, char *word, int count) {
    if (!(*root))
        *root = createNode(*word);

    if ((*word) < (*root)->data)
        insertTrieCount(&( (*root)->left ), word, count);
    else if ((*word) > (*root)->data)
        insertTrieCount(&( (*root)->right ), word, count);
    else
    {
        if (*(word+1))
            insertTrieCount(&( (*root)->eq ), word+1, count);
        else{
            (*root)->count+=count;
            (*root)->isLeaf = 1;
        }
    }
}


void print_trie(trieNode* root, FILE *fp) {
    if (!root)
        return;
    char word[MAX];
    int depth = 0;
    printTrieRec(root, word, depth, fp);
}

void printTrieRec(trieNode* root, char *word, int depth, FILE *fp) {
    if (!root)
        return;
    trieNode *temp = root;
    printTrieRec(temp->left, word, depth, fp);

    word[depth] = temp->data;
    if (temp->isLeaf){
        word[depth + 1] = '\0';
        fprintf(fp,"%s\t%d\n", word, temp->count);
    }

    printTrieRec(temp->eq, word, depth + 1, fp);

    printTrieRec(temp->right, word, depth, fp);
}

void deleteTrie(trieNode** root) {
    if ((*root)->left != NULL)
        deleteTrie(&(*root)->left);

    if ((*root)->eq != NULL)
        deleteTrie(&(*root)->eq);

    if ((*root)->right != NULL)
        deleteTrie(&(*root)->right);

    free(*(root));
    *(root) = NULL;
}

