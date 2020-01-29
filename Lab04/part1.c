#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include<time.h>
 
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
 
// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)
 
// Converts key current character into indexNumber
// use only 'a' through 'z' and lower case
#define CHAR_TO_indexNumber(c) ((int)c - (int)'a')

#define indexNumber_TO_CHAR(c) ((int)c + (int)'a')

int nodeCount = 0;
// trie node
typedef struct trienode
{
    struct trienode *children[ALPHABET_SIZE];
 
    // isEndOfWord is true if the node represents
    // end of a word
    bool isEndOfWord;

    //struct TrieNode * parent;
   
}TrieNode;
 
// Returns new trie node (initialized to NULLs)
TrieNode * createNode(void)
{
   TrieNode *parentNode = NULL;
 
    parentNode = (TrieNode *)malloc(sizeof(TrieNode));
 
    if (parentNode)
    {
        int i;
 
        parentNode->isEndOfWord = false;
 
        for (i = 0; i < ALPHABET_SIZE; i++)
            parentNode->children[i] = NULL;
            nodeCount++;
    }
 
    return parentNode;
}
 
// If not present, insertWords key into trie
// If the key is prefix of trie node, just marks leaf node
void insertWord(TrieNode *root, const char *key)
{
    int branch;
    int length = strlen(key);
    int indexNumber;
 
    TrieNode *pCrawl = root;
 
    for (branch = 0; branch < length; branch++)
    {
        indexNumber = CHAR_TO_indexNumber(key[branch]);
        if (!pCrawl->children[indexNumber])
            pCrawl->children[indexNumber] =  createNode();
 
        pCrawl = pCrawl->children[indexNumber];
    }
 
    // mark last node as leaf
    pCrawl->isEndOfWord = true;
}


char suggestion[20] = {};
char temp[20] = {};
int size = 0;

void printSuggestion(TrieNode * n){
    int i=0;
    if(n->isEndOfWord) {
        temp[size] = '\0';
        printf("Suggest Words : %s%s\n", suggestion,temp);
    }
    for(i=0;i<ALPHABET_SIZE;i++){
        if(n->children[i]){
            temp[size] = (char) indexNumber_TO_CHAR(i);
            size++;
            printSuggestion(n->children[i]);
            size--;
        }
    }
}
 
// Returns true if key presents in trie, else false
bool printSuggestions(TrieNode *root, const char *key)
{
    int count = 0;
    int branch;
    int length = strlen(key);
    int indexNumber;
    TrieNode *pCrawl = root;
 
    for (branch = 0; branch < length; branch++)
    {
        indexNumber = CHAR_TO_indexNumber(key[branch]);
 
        if (!pCrawl->children[indexNumber])
            return false;

        suggestion[count] = (char) indexNumber_TO_CHAR(indexNumber);
        count++;
 
        pCrawl = pCrawl->children[indexNumber];
    }

    //------------------------------------
    suggestion[count] = '\0';
    printSuggestion(pCrawl);

    return (pCrawl != NULL && pCrawl->isEndOfWord);
}

// Driver
int main()
{
    FILE * pFile;

    pFile = fopen("wordlist70000.txt","r");
    char temp[20];

    TrieNode *root =  createNode();
    clock_t begin = clock();
    
    while(!feof(pFile)){
        
        fscanf(pFile,"%s",temp);
        //one word
        int j = 0;
        while(temp[j]){
            if(isupper(temp[j])) temp[j] = tolower(temp[j]);
            j++;
        }
        insertWord(root, temp);
        
    }

    fclose(pFile);
    clock_t end = clock();
    double elapsedtime = (double)(end-begin)/CLOCKS_PER_SEC;
    printf("Elapsed time to store: %f s\n",elapsedtime);

   char Suggestion[25] = {};

   while(1){
        clock_t begin = clock();
        printf("Search Here : ");
        scanf("%s",Suggestion);
        printf("\n");
        printSuggestions(root, Suggestion);
        printf("\n\n");
        clock_t end = clock();
        double elapsedtime = (double)(end-begin)/CLOCKS_PER_SEC;
        printf("Elapsed time to search: %f s\n",elapsedtime);
        printf("Memory: %d Bytes",sizeof(*(root))*nodeCount);
   }
 
    return 0;
}