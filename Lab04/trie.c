#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h> 

typedef struct trienode{

	TrieNode * children[26];

	bool isEndOfWord;

}TrieNode;

TrieNode * createNode(void){

	TrieNode *pNode = NULL; 
  
    pNode = (TrieNode *)malloc(sizeof(TrieNode)); 
  
    if (pNode) 
    { 
        int i; 
  
        pNode->isEndOfWord = false; 
  
        for (i = 0; i < 26; i++) 
            pNode->children[i] = NULL; 
    } 
  
    return pNode;
}

void insert(TrieNode *root, const char *key) 
{ 
    int level; 
    int length = strlen(key); 
    int index; 
  
    TrieNode *pCrawl = root; 
  
    for (level = 0; level < length; level++) 
    { 
        index = (int)key[level] - (int)'a'; 
        if (!pCrawl->children[index]) 
            pCrawl->children[index] = createNode(); 
  
        pCrawl = pCrawl->children[index]; 
    } 
  
    // mark last node as leaf 
    pCrawl->isEndOfWord = true; 
}

bool search(TrieNode *root, const char *key) 
{ 
    int level; 
    int length = strlen(key); 
    int index; 
    TrieNode *pCrawl = root; 
  
    for (level = 0; level < length; level++) 
    { 
        index = (int)key[level] - (int)'a'; 
  
        if (!pCrawl->children[index]) 
            return false; 
  
        pCrawl = pCrawl->children[index]; 
    } 
  
    return (pCrawl != NULL && pCrawl->isEndOfWord); 
}  

int main (){

	FILE * fp;

	char word_arr [1000][1000];
	char ch;

	int countVertical = 0;
	int countHorizontal = 0;

	char * fileName = "./wordlist1000.txt";

	fp = fopen (fileName, "r");

	if(fp == NULL){
		printf("Couldn't open the destinated file\n");
		return 1;
	}

	while((ch = fgetc(fp)) != EOF){
		//printf("%c",ch);
		if(ch == '\n'){
			countHorizontal ++;
			//printf("%d  %d\n",countHorizontal,countVertical);
			countVertical = 0;
			//printf("%s\n",word_arr[countHorizontal-1][0]);
		}else{
			word_arr[countHorizontal][countVertical] = ch;
			//printf("%c\n",word_arr[countHorizontal][countVertical]);
			countVertical ++;
		}
		
	}
	/*for(int i =0;i<1000;i++){
		for(int j =0;j<10;j++){
			printf("%c",word_arr[i][j]);
		}
		printf("\n");
	}*/
	fclose(fp);



	return 0;
}