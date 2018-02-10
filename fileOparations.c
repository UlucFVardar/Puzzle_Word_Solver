#include <stdio.h>
#include <stdlib.h>
#include "fileOparations.h"
#include <string.h>
#include <ctype.h>
int openAndCountFile(char* file){
FILE *pToFile = fopen(file,"r");
	int line = 0;
	char input[512];
	while( fgets( input, 512, pToFile )) {
		line++;
	}
	fclose(pToFile);
return line;
}

 void openAndReadFile( char *file ,int m,char *worlds[m]){
	FILE *pToFile = fopen(file,"r");
	int line = 0;
	char input[512];
	int i;
	while( fgets( input, 512, pToFile )) {
		worlds[line] = malloc(strlen(input)+1);		
		for(i=0 ; i< strlen(input); i++){
				input[i]=(char)toupper((int)input[i]);
			}
        	strcpy(worlds[line], input  );
		line++;
	}
fclose(pToFile);


}
