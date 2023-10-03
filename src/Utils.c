/*File that contains source code of various functions*/
#include <stdio.h>
#include <string.h>

#include "Utils.h"

void red(){
 	printf("\033[1;31m");
}

void green(){
	printf("\033[1;32m");
}

void reset(){
 	printf("\033[0m");
}


int line_counter(char* input){
	FILE* fp = fopen(input, "r");		/*Create pointer to opened file*/
	int counter = 0;
	int value;

	while((value = fgetc(fp)) != EOF){	/*Each time new line is found increase counter*/
		
		if(value == '\n')
			counter++;
	}
	
	fclose(fp);							/*Close file and free allocated space*/
	return counter;
}


DB create_db(char* name){
	DB myDB = NULL;
	int rc = sqlite3_open(name, &myDB);

	if(rc){
		fprintf(stderr, "Error: Cannot open/create database -> %s \t Code: %s\n", name, sqlite3_errmsg(myDB));
		return 0;	
	}
	return myDB;
}
