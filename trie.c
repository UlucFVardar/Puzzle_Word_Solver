
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "trie.h"
#define ALPHABET_SIZE (26)
#define CHAR_TO_INDEX(c) ((int)c - (int)'A')

struct TrieNode *newNode()
{
    struct TrieNode *pNode = NULL;
    pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (pNode)
    {
        int i;
        pNode->aWord = false;
        pNode->numberoFChildren=0;
        for (i = 0; i < ALPHABET_SIZE; i++)
            pNode->children[i] = NULL;
    }
    return pNode;
}
void add(struct TrieNode *root,  char *word)
{
	//printf("'->%s \n",word);
    int i;
    int length = strlen(word);
    int index;
    struct TrieNode *tempNode = root;
    for ( i = 0; i<length-1 ; i++ )
    {
        index = CHAR_TO_INDEX(word[i]);
        if(i==0)
        {
            tempNode=tempNode->children[index];
            continue;
        }
        if (!tempNode->children[index])
            tempNode->children[index] = newNode();

        tempNode->numberoFChildren++;
        tempNode->key=word[i];
        tempNode = tempNode->children[index];

    }
    tempNode->aWord = true;
}
bool Search(struct TrieNode *root,  char *Key)
{
    int i;
    int length = strlen(Key);
    int index;
    struct TrieNode *pCrawl = root;
    for (i = 0; i < length; i++)//-1 for because for every line program takes \n and to dont calculate it used this.!!!!!!
    {
        index = CHAR_TO_INDEX(Key[i]);

        if (!pCrawl->children[index])
        {
            return false;
        }
        pCrawl = pCrawl->children[index];
    }
return pCrawl->aWord;
}

void Remove(struct TrieNode *rootnode, char *word)
{
    int i;
    int length = strlen(word);
    int index;
    struct TrieNode *pCrawl = rootnode;
    index = CHAR_TO_INDEX(word[0]);
    pCrawl=pCrawl->children[index];
    for (i = 0; i < length-1; i++)//-1 for because for every line program takes \n and to dont calculate it used this.!!!!!!
    {
        index = CHAR_TO_INDEX(word[i]);
        if (    (pCrawl->numberoFChildren<=1 ) )
        {
            printf("tur %d siliniyor...%c",i,pCrawl->key);
            pCrawl->children[(int)CHAR_TO_INDEX(word[i+1])]=NULL;
            pCrawl=NULL;
            return;
        }
        pCrawl = pCrawl->children[index];
    }
}


/*

            void removeall(struct trienode *rootnode);

            int  Size(struct trienode *rootnode);
            int isempty(struct trienode *rootnode);//bool
            int countwordswithprefix(struct trienode *root, char *prefix);
            void printwordswithprefix(struct trienode *root, char *prefix);
*/
