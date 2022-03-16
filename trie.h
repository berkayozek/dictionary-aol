typedef struct trieNode{
    char data;
    struct trieNode *left, *eq, *right;
    int isLeaf;
    int count;
}trieNode;

trieNode* createNode(char data);
void insertTrie(trieNode **root, char  *word);
void insertTrieCount(trieNode **root, char *word, int count);
int search_trie(trieNode** root, char * word);
void print_trie(trieNode* root, FILE *fp);
void printTrieRec(trieNode* root, char *word, int depth, FILE *fp);
void deleteTrie(trieNode** root);
