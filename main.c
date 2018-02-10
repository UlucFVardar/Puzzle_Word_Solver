#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "trie.h"
#include "puzzel.h"
#include <string.h>
#include "fileOparations.h"
#define CHAR_TO_INDEX(c) ((int)c - (int)'A')
//#define FILE_NAME "TurkishWords.txt" //when I use this dictionary I take core dumped error
#define FILE_NAME "Deneme.txt"
#define ALPHABET_SIZE (26)
#define MATRIX_SIZE 6
#define WORD_SIZE 6


int** generateMatrix();
void showMatrix(int** puzzel);
void result(struct puzzelwords *list);
void generateTheTrieFromFile(struct TrieNode *firstRoot);
void makeSetUpSettingToFirstSegmentOfTrie(struct TrieNode *firstRoot);
void generateAllTrie( struct TrieNode *firstroot,int dictionarySize,char *allWorlds[] );
void  findPossibleWordsUsingRecursiveFunction(struct puzzelwords *list,struct TrieNode *trie,int **puzzle);
void findAllPossibleWordsInThePuzzelAndThemToList(int x,int y,char *addingW,int depth,int **puzzle,struct puzzelwords *firstRoot,struct TrieNode *trie,bool done[MATRIX_SIZE][MATRIX_SIZE]);


int main(){
    // Part1 //generate randomMatrix
    int** puzzle=generateMatrix();
    showMatrix(puzzle);
    // part 1 end

    // part4 //Build Turkish dictionary Trie
    struct TrieNode *firstRoot=newNode();
    makeSetUpSettingToFirstSegmentOfTrie(firstRoot);
    generateTheTrieFromFile(firstRoot);
    // part4 end

    // Part 2,3,5
    struct puzzelwords *randomGeneratedWords1to6LinkedList;
    randomGeneratedWords1to6LinkedList=newWord();
    findPossibleWordsUsingRecursiveFunction(randomGeneratedWords1to6LinkedList,firstRoot,puzzle);
    // Part 2,3,5 end
    // this scope, checks its a valid ramdom word or not by one by when adding to linked list operation is being made

    // peek the result
    result(randomGeneratedWords1to6LinkedList);
    return 0;
}

int** generateMatrix(){

    //{'A','B','C','Ç','D','E','F','G','Ð','H','Ý','I','J','K','L','M','N','O','Ö','P','R','S','Þ','T','U','Ü','V','Y','Z'};
    int letters [] = {65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90};
    int i,j;
    int* values = calloc(MATRIX_SIZE*MATRIX_SIZE, sizeof(int));
    int** rows = malloc(MATRIX_SIZE*sizeof(int*));
    srand(time(NULL));
    for ( i=0; i<MATRIX_SIZE; ++i)
    {
        rows[i] = values + i*MATRIX_SIZE;
    }
    for(i=0 ; i < MATRIX_SIZE ; i++ )
    {
        for(j=0 ; j< MATRIX_SIZE ; j++ )
        {
            rows[i][j]=letters[rand()%ALPHABET_SIZE];
        }
    }

    return  rows;
}
void showMatrix(int** puzzel){
    int i,j;
    printf("\n\t\t");
    for(i=0 ; i < MATRIX_SIZE ; i++ )
    {
        for(j=0 ; j< MATRIX_SIZE ; j++ )
        {
            printf("%c ",puzzel[i][j]);
        }
        printf("\n\t\t");
    }
    printf("\n-------------------Test------------------\n");
}
void result(struct puzzelwords *list){
    char outPut[][60] = {"Random generated word is Not present in trie\n","Random generated word is Present in trie(in File)!\n"};
    while( list->next!=NULL ){
        if(list->valid)
            printf("%7s ->%s \n",list->word,outPut[list->valid]);
        list=list->next;
    }
}
void generateAllTrie( struct TrieNode *firstroot,int dictionarySize,char *allWorlds[] ){
    int i;
    for( i=0 ; i<dictionarySize ; i++)
    {

	//printf("%7s ->",allWorlds[i]);
        add(firstroot,allWorlds[i]);

    }

}
void makeSetUpSettingToFirstSegmentOfTrie(struct TrieNode *firstRoot){
    firstRoot->key='\0';
     firstRoot->aWord=false;
    firstRoot->numberoFChildren=0;
    int i,j;

    char alphabet [ALPHABET_SIZE]= {65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90};
        for( i=0 ; i<ALPHABET_SIZE ; i++  )
        {
            int index;
            index = CHAR_TO_INDEX(alphabet[i]);
            firstRoot->children[index] = newNode();
            firstRoot->children[index]->key=(char)(alphabet[i]);
            firstRoot->children[index]->aWord=false;
            firstRoot->numberoFChildren++;
        }

}
void generateTheTrieFromFile(struct TrieNode *firstRoot){
    int dictionarySize=openAndCountFile(FILE_NAME);
    char *allWorlds[dictionarySize];
    openAndReadFile(FILE_NAME,dictionarySize,allWorlds);
    generateAllTrie(firstRoot,dictionarySize,allWorlds);
}
void  findPossibleWordsUsingRecursiveFunction(struct puzzelwords *list,struct TrieNode *trie,int **puzzle){
    int i,j;
    struct puzzelwords *tail=newWord();
    list->next=tail;
    tail->backward=list;
    bool done[MATRIX_SIZE][MATRIX_SIZE];
    for(i=0 ; i<MATRIX_SIZE ; i++)
        for(j=0 ; j<MATRIX_SIZE ; j++)
            done[i][j]=false;

    printf("\n    All Possibilitys are being calculated...\n\n");
    for(i=0 ; i<MATRIX_SIZE ; i++)
        for(j=0 ; j<MATRIX_SIZE ; j++)
            findAllPossibleWordsInThePuzzelAndThemToList(i,j,"",0,puzzle,list,trie,done) ;
    printf("\t\tDone!\n\n\n");

}
void findAllPossibleWordsInThePuzzelAndThemToList(int x,int y,char *addingW,int depth,int **puzzle,struct puzzelwords *firstRoot,struct TrieNode *trie,bool done[MATRIX_SIZE][MATRIX_SIZE])
{
    int i,j;
    bool copyDone [MATRIX_SIZE][MATRIX_SIZE];
    for(i=0 ; i<MATRIX_SIZE ; i++)
        for(j=0 ; j<MATRIX_SIZE ; j++)
            copyDone[i][j]=done[i][j];
    if( x < 0 || x > MATRIX_SIZE-1 || y < 0 ||y > MATRIX_SIZE-1 || depth >=WORD_SIZE || (copyDone[x][y]==true) )
    {
        return ;
    }
    copyDone[x][y]=true;
    size_t len=strlen(addingW);
    char *str2=malloc(len+1+1);
    strcpy(str2,addingW);
    str2[len]=(char)puzzle[x][y];
    str2[len+1]='\0';
    Add(firstRoot,str2 );
    firstRoot->next->valid=Search(trie,str2); //this is for is this a valid word or not
    //printf("%s \n",firstRoot->next->word); //for printing all words that added to list

    /*
    findAllPossibleWordsInThePuzzelAndThemToList(x-1,y-1,str2,depth+1,puzzle,firstRoot,trie,copyDone);
    findAllPossibleWordsInThePuzzelAndThemToList(x-1,y,str2,depth+1,puzzle,firstRoot,trie,copyDone);
    findAllPossibleWordsInThePuzzelAndThemToList(x-1,y+1,str2,depth+1,puzzle,firstRoot,trie,copyDone);
    findAllPossibleWordsInThePuzzelAndThemToList(x,y-1,str2,depth+1,puzzle,firstRoot,trie,copyDone);
    findAllPossibleWordsInThePuzzelAndThemToList(x,y+1,str2,depth+1,puzzle,firstRoot,trie,copyDone);
    findAllPossibleWordsInThePuzzelAndThemToList(x+1,y-1,str2,depth+1,puzzle,firstRoot,trie,copyDone);
    findAllPossibleWordsInThePuzzelAndThemToList(x+1,y,str2,depth+1,puzzle,firstRoot,trie,copyDone);
    findAllPossibleWordsInThePuzzelAndThemToList(x+1,y+1,str2,depth+1,puzzle,firstRoot,trie,copyDone);
    */// OR
    int xWay[]={-1,-1,-1,0,0,1,1,1};
    int yWAy[]={-1,0,1,-1,1,-1,0,1};
    for(i=0 ; i<8 ; i++)
        findAllPossibleWordsInThePuzzelAndThemToList(x+xWay[i],y+yWAy[i],str2,depth+1,puzzle,firstRoot,trie,copyDone);
}


