#ifndef TRIE_H
#define TRIE_H
#include <stdbool.h>
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
#define ALPHABET_SIZE (26)
#define CHAR_TO_INDEX(c) ((int)c - (int)'A')


struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    char key;
    int numberoFChildren;
    bool aWord;
};

struct TrieNode *newNode();
void add(struct TrieNode *root,  char *key);
bool Search(struct TrieNode *root,  char *key);//bool
void Remove(struct TrieNode *rootnode, char *word);
void printt(struct TrieNode *rootnode);
//  int  Size(struct TrieNode *rootnode);
//  int isempty(struct TrieNode *rootnode);//bool
//  int countwordswithprefix(struct TrieNode *root, char *prefix);
//  void printwordswithprefix(struct TrieNode *root, char *prefix);
//  void removeall(struct TrieNode *rootnode);
#endif // FILEOPARATIONS_H_INCLUDED
