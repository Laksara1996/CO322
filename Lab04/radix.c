#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>

int nodeCount=0;
int charNodeCount=0;

typedef struct charNode
{
	char letter;
	struct charNode *next;
}charNode;

typedef struct trieNode
{
    struct trieNode *children[26];
    charNode * word;
    bool endOfWord;
}trieNode;



charNode* createCharNode(char letter)
{
    charNode* newNode = (charNode*) malloc(sizeof(charNode));
    newNode -> letter = letter;
    newNode -> next = NULL;
    charNodeCount++;
    return newNode;
}

int getCharIndex(char c)
{   
    if(c>96 && c<123){
        return c-97;
    }else if(c>64 && c<91){
        return c-65;
    }else{
        return -1;
    }
}

trieNode* createNode()
{
    trieNode* newtrieNode = (trieNode*)malloc(sizeof(trieNode));
    newtrieNode->endOfWord = false;
    newtrieNode->word = NULL;
    int i;
    for (i = 0; i<26; i++)
    {
    	newtrieNode->children[i] = NULL;
    }
    nodeCount++;
    return newtrieNode;
    
}

bool isLeafNode(trieNode* node){
   bool haschildren = false;
   for(int i=0;i<26;i++){
      if(node->children[i] != NULL){
          haschildren =true;
          break;
      }
   }
   return !(haschildren || node->endOfWord);
}


int findMissMatchNode(trieNode* root,char* word,trieNode** prevNode,trieNode** currentNode,charNode ** ptempChar,charNode ** ctempChar){

    *currentNode = root;
    int i=0;
    for(i=0;i<strlen(word);i++){
        int charIndex = getCharIndex(word[i]);
        if(charIndex == -1){
            continue;
        }
        if((*currentNode)==root && (*currentNode)->children[charIndex]==NULL){
        return i;
        }else if((*currentNode)==root && (*currentNode)->children[charIndex]!=NULL){
          (*prevNode)=(*currentNode);
          (*currentNode) = (*currentNode)->children[charIndex];
          (*ptempChar) = (*currentNode)->word;
          (*ctempChar) = (*currentNode)->word->next;
          continue;
        }
        if((*ctempChar) != NULL){
           if((*ctempChar)->letter == word[i]){
                *ptempChar = *ctempChar;
                *ctempChar = (*ctempChar)->next; 
                continue;
           }else{
                return i;  //ctempchar points to invalid letter;
           }
        }else{
            if((*currentNode)->children[charIndex]!=NULL){
                *prevNode=*currentNode;
                *currentNode = (*currentNode)->children[charIndex];
                *ptempChar = (*currentNode)->word;
                *ctempChar = (*currentNode)->word->next;
                continue; 
            }else{
                return i;  //ctempchar ==null
            }
        }
    }
    return i;
}

void insertWord(trieNode* root,char* word)
{ 
    trieNode* prevNode=NULL;
    trieNode* currentNode=NULL;
    charNode* ptempChar=NULL;
    charNode* ctempChar=NULL;
    int windex = findMissMatchNode(root,word,&prevNode,&currentNode,&ptempChar,&ctempChar);
    
    if(currentNode==root){
        int charIndex =getCharIndex(word[windex]);
        currentNode->children[charIndex]=createNode();
        currentNode = currentNode->children[charIndex];
        currentNode->word = createCharNode(word[windex]);
        ctempChar=currentNode->word;
        for(int i = windex+1;i<strlen(word);i++){
               ctempChar->next= createCharNode(word[i]);
               ctempChar=ctempChar->next;
        }
        currentNode->endOfWord =true;
        return;
    }else if( ctempChar == NULL){
        if(currentNode->endOfWord){
            while(windex < strlen(word) && getCharIndex(word[windex]) == -1){
               windex++;
            } 
            int charIndex =getCharIndex(word[windex]);
            currentNode->children[charIndex] = createNode();
            currentNode = currentNode->children[charIndex];
            currentNode->word = createCharNode(word[windex]);
            ctempChar=currentNode->word;
            for(int i = windex+1;i<strlen(word);i++){
               if(getCharIndex(word[i])==-1){
                 continue;
               }
               ctempChar->next= createCharNode(word[i]);
               ctempChar=ctempChar->next;
            }
            currentNode->endOfWord =true; 
        }else{
            if(isLeafNode(currentNode)){
                for(int i = windex;i<strlen(word);i++){
                    if(getCharIndex(word[i])==-1){
                        continue;
                    }
                ptempChar->next= createCharNode(word[i]);
                ptempChar=ptempChar->next;
                }
            }
             currentNode->endOfWord =true;
        }
        return;
    }else if(ctempChar != NULL ){
        if(windex < strlen(word)){
           int charIndex = getCharIndex(currentNode->word->letter);
           prevNode->children[charIndex]=createNode();
           prevNode=prevNode->children[charIndex];
           prevNode->word = currentNode->word;
           currentNode->word=ctempChar;
           ptempChar->next =NULL;
           prevNode->children[getCharIndex(currentNode->word->letter)]=currentNode;
           prevNode->children[getCharIndex(word[windex])] = createNode();
           currentNode = prevNode->children[getCharIndex(word[windex])]; 
           currentNode->word = createCharNode(word[windex]);
            ctempChar=currentNode->word;
            for(int i = windex+1;i<strlen(word);i++){
               if(getCharIndex(word[i])==-1){
                 continue;
               }
               ctempChar->next= createCharNode(word[i]);
               ctempChar=ctempChar->next;
            }
            currentNode->endOfWord =true; 
        }else{
           int charIndex = getCharIndex(currentNode->word->letter);
           prevNode->children[charIndex]=createNode();
           prevNode=prevNode->children[charIndex];
           prevNode->word = currentNode->word;
           ptempChar->next =NULL;
           prevNode->endOfWord =true;
           currentNode->word=ctempChar;
           prevNode->children[getCharIndex(currentNode->word->letter)]=currentNode;
           return;
        }
    } 
}

trieNode* makeTrie(FILE* fp)
{
    char word[100];
    
    if (fp == NULL)
    {
        return NULL;
    }
    clock_t begin = clock();
    trieNode* root = createNode();
    root->word=createCharNode('/');
    while(!feof(fp))
    {
        fgets(word,100,fp);
        insertWord(root,word);
    }
    clock_t end = clock();
    double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
    return root;
}

trieNode* searchForMatch(trieNode* root,char* word)
{
    int i,charIndex;
    trieNode* currentNode = root;
    charIndex = getCharIndex(word[0]);
    if(charIndex==-1){
        return NULL;
    }
    currentNode = currentNode->children[charIndex];
    if(currentNode==NULL){
        return NULL;
    }
    charNode * tempchar = currentNode->word;
    int k=0;
    int l=0;
    for(i=0;i<strlen(word);i++)
    {   
        if((tempchar!=NULL) && tempchar->letter == word[i]){
          tempchar=tempchar->next;
          continue;
        }else if((tempchar!=NULL) && tempchar->letter != word[i]){
          return NULL;
        }
        if(tempchar==NULL){
            k=i;
            charIndex = getCharIndex(word[i]);
            currentNode =currentNode->children[charIndex];
            if(currentNode == NULL){
                return NULL;
            }
            tempchar = currentNode->word->next;
        } 
    }
    for(int j=k;j<strlen(word);j++){
       word[j]=0;
    }
    return currentNode;
}


void printFromNode(trieNode* Node,char charBuffer[],int textSize)
{   
    int i,charIndex;
    if(Node->endOfWord)
    {
        for(i=0;i<textSize;i++)
        {   
            printf("%c",charBuffer[i]);
        }
        charNode * temp =Node->word;
            while(temp != NULL){
            printf("%c",temp->letter);
            temp=temp->next;
        }
        printf("\n");
    }
    for(i=0;i<26;i++)
    {
        if(Node->children[i]!=NULL)
        {   int templen=0; 
            charNode * temp =Node->word;
            while(temp != NULL){
            charBuffer[textSize+templen] =temp->letter;
            temp=temp->next;
            templen++;
            }
            printFromNode(Node->children[i],charBuffer,textSize+templen);
        }
    }
}

 

int main()
{
    char Suggestion[25];
    FILE *fp = fopen("wordlist70000.txt","r");
    clock_t begin = clock();
    trieNode* root = makeTrie(fp);
    clock_t end = clock();
    double elapsedtime = (double)(end-begin)/CLOCKS_PER_SEC;
    printf("Elapsed time to store: %f s\n",elapsedtime);
    fclose(fp);
    if(root ==NULL){
        exit(1);
    }
     
    printf("Memory for Trie nodes: %d Bytes , No of TrieNodes: %d \n",sizeof(*(root))*nodeCount,nodeCount);
    printf("Memory for char nodes: %d Bytes , No of CharNodes: %d \n",sizeof(charNode)*charNodeCount,charNodeCount);
    printf("\n");
    while(1)
    {
        printf("Search Here : ");
        scanf("%s",&Suggestion);
        char str[100];
        strcpy(str,Suggestion);
        clock_t begin = clock();
        printf("\nSuggested Words\n\n");
        trieNode* suggestedNode = searchForMatch(root,str);
        printFromNode(suggestedNode,str,strlen(str));
        clock_t end = clock();
        double elapsedtime = (double)(end-begin)/CLOCKS_PER_SEC;
        printf("\nElapsed time to search: %f s\n",elapsedtime);
         
    } 
    return 0;
}