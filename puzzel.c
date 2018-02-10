#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "puzzel.h"

struct puzzelwords *newWord()
{
    struct puzzelwords *pNode = NULL;
    pNode = (struct puzzelwords *)malloc(sizeof(struct puzzelwords));
    pNode->valid=false;
    pNode->next=NULL;
    pNode->backward=NULL;
    return pNode;
}

void Add(struct puzzelwords *wordRoot,char *word)
{
    
    struct puzzelwords *temp=newWord();
    strcpy(temp->word, word);
    temp->next=wordRoot->next;
    wordRoot->next->backward=temp;
    wordRoot->next=temp;
    temp->backward=wordRoot;
}

void printLinkedList(struct puzzelwords *wordRoot){
    while(wordRoot->next!=NULL){
        printf("'->%s \n",wordRoot->word);
        wordRoot=wordRoot->next;
    }
}


