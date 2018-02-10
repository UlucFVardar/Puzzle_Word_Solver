#ifndef PUZZEL_H
#define PUZZEL_H
#include <stdbool.h>


struct puzzelwords
{

    char word[6];
    bool valid;
    struct puzzelwords *next;
    struct puzzelwords *backward;
};
struct puzzelwords *newWord();
void Add(struct puzzelwords *WORD,char *word);

#endif
