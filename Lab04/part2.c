#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>

int nodeCount=0;

typedef struct linkedString
{
	char letter;
	struct linkedString *next;
}linkedString;

typedef struct trieNode
{
    struct trieNode* children[26];
    linkedString* linkedString;
    bool endOfWord;
}trieNode;

int getCharIndex(char c)
{
    return c-'a';
}

linkedString* createString(char newLetter)
{
    linkedString* newString = (linkedString*) malloc(sizeof(linkedString));
    newString -> letter = newLetter;
    newString -> next = NULL;
    return newString;
}

trieNode* createNode()
{
    trieNode* newtrieNode = (trieNode*)malloc(sizeof(trieNode));
    newtrieNode->linkedString = NULL;
    newtrieNode->endOfWord = false;
    int i;
    for (i=0;i<26;i++)
    {
    	newtrieNode->children[i] = NULL;
    }
    return newtrieNode;
}

linkedString* linkedStringAppend(char* str,int inital,int end)
{
    int i;
    linkedString* current = createString(str[inital]);
    linkedString* newString = NULL;
    linkedString* string = current;

    for(i=inital+1;i<end;i++)
    {
        newString = createString(str[i]);
        current->next = newString;
        current = current->next;
    }
    current = NULL;
    return string;
}

trieNode* linkedStringBreak(trieNode* previousNode,trieNode* node,linkedString* breakPoint)
{
    trieNode* newNode = createNode();
    linkedString* newString = breakPoint->next;
    breakPoint->next = NULL;
    int index1 = getCharIndex(newString->letter);

    newNode->linkedString = node->linkedString;
    node->linkedString = newString;
    newNode->children[index1] = node;

    int index2 = getCharIndex(newNode->linkedString->letter);
    previousNode->children[index2] = newNode;

    return newNode;
}

void insertNode(trieNode* root,char* word)
{
    int lastLetterIndex = strlen(word)-1;
    int i=0,charIndex;

    trieNode* currentNode = root, *previousNode = NULL;
    trieNode* newNode = NULL;
    linkedString* currentLetter, *previousLetter = NULL;
    currentLetter = currentNode->linkedString;
    while(i<lastLetterIndex)
    {
    	charIndex = getCharIndex(word[i]);
    	if(currentLetter == NULL)
        {
    		if(currentNode->children[charIndex] == NULL)
    		{
    			newNode = createNode();
    			newNode->linkedString = linkedStringAppend(word,i,lastLetterIndex);
                newNode->endOfWord = true;
    			currentNode->children[charIndex] = newNode;
    			nodeCount = nodeCount+1;
    			break;
    		}
    		else
            {
                previousNode = currentNode;
                currentNode = currentNode->children[charIndex];
                previousLetter = currentNode->linkedString;
    			currentLetter = currentNode->linkedString->next;
    		}
    	}
        else
        {
    		if (currentLetter->letter != word[i])
    		{
    			currentNode = linkedStringBreak(previousNode,currentNode,previousLetter);
    			newNode = createNode();
    			newNode->linkedString = linkedStringAppend(word,i,lastLetterIndex);
                newNode->endOfWord = true;
    			currentNode->children[charIndex] = newNode;
    			break;
    		}
            else
            {
                previousLetter = currentLetter;
    			currentLetter = currentLetter->next;
    		}
    	}
    	i++;
    }
}

trieNode* fileReader(char* fileName)
{
    char word[60];
    FILE *fp = fopen(fileName,"r");
    if (fp == NULL)
    {
        printf("Unable to open the file");
        exit(1);
    }
    trieNode* root = createNode();
    clock_t begin = clock();
    while(1)
    {
        fgets(word,60,fp);
        insertNode(root,word);
        if(feof(fp))
            break;
    }
    clock_t end = clock();
    double time_spent = (double)(end-begin)/CLOCKS_PER_SEC;
    printf("%.8lf s\n",time_spent);
    fclose(fp);
    return root;
}

trieNode* searchNodes(trieNode* root,char* word)
{
    int lastIndex = strlen(word);
    int i=0,charIndex;
    trieNode* currentNode = root;
    linkedString* currentLetter = currentNode->linkedString;

    while(i<lastIndex)
    {
    	charIndex = getCharIndex(word[i]);

    	if(currentLetter == NULL)
        {
            currentNode = currentNode->children[charIndex];
    		currentLetter = currentNode->linkedString->next;
    	}
        else
        {
    		currentLetter = currentLetter->next;
    	}
        i++;
    }

    while(currentLetter != NULL)
    {
    	word[lastIndex] = currentLetter->letter;
    	currentLetter = currentLetter->next;
    	lastIndex++;
    }
    word[lastIndex] = '\0';
    return currentNode;
}

int stringToChar(linkedString* begin,char* str,int initial)
{
    int newSize = initial;
    linkedString* currentLetter = begin;

    while (currentLetter != NULL)
    {
        str[newSize] = currentLetter->letter;
        newSize++;
        currentLetter = currentLetter->next;
    }
    str[newSize] = '\0';
    return newSize-1;
}


void printSuggetions(trieNode* suggestedNode,char wordBuffer[],int bufferSize)
{
    trieNode* currentNode = suggestedNode;
    int i,j,newSize;

    if(currentNode->endOfWord)
    {
        for (j=0;j<bufferSize;j++)
        {
            printf("%c",wordBuffer[j]);
        }
        printf("\n");
    }

    for (i=0;i<26;i++)
    {
        if(currentNode->children[i]!=NULL)
        {
            newSize = stringToChar(currentNode->children[i]->linkedString,wordBuffer,bufferSize);
            printSuggetions(currentNode->children[i],wordBuffer,newSize+1);
        }
    }
}

int main()
{
    char text[100];
    trieNode* root = fileReader("wordlist1000.txt");
    while(1)
    {
        printf("Enter keyword: ");
        scanf("%s",&text);
        char str[60];
        strcpy(str,text);
        clock_t begin = clock();
        trieNode* suggestedNode = searchNodes(root,str);
        printf("Suggested Words\n");
        printf("-----------------------\n");
        printSuggetions(suggestedNode,str,strlen(str));
        clock_t end = clock();
        double elapsedtime = (double)(end-begin)/CLOCKS_PER_SEC;
        printf("Elapsed time: %f s\n",elapsedtime);
        printf("Memory: %d Bytes",sizeof(*(root))*nodeCount);
        printf("\n");
    }
    return 0;
}