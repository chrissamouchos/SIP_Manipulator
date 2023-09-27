/*---------- Start of System Libraries ------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
/*---------- End of System Libraries --------------*/

/*---------- Start of Custom Libraries ------------*/
#include "Utils.h"
/*---------- End of Custom Libraries --------------*/

/*---------- Start of Main function ---------------*/
int main(int argc, char** argv){
	printf("Start of execution...\n");
	char* input_file = NULL;
	int c;

	/* -------------Get Options of Command line--------------*/
	while( (c = getopt(argc,argv,"i:")) != -1){
		switch(c){
			case 'i':
				input_file = optarg;
				break;
			case '?':
				return 1;
		}	
	}
	/*---------------End of Options Parsing----------------*/

	if(!input_file){		/*Check if input file is not given, print error, terminate*/
		printf("Input file is mandatory, none was given\n");
		return 1;
	}

	size_t size;
	char** args;

	int num_of_lines = line_counter(input_file);
	FILE* fp = fopen(input_file, "r"); 	/*Open input file to parse it's data*/
	char* line = NULL;					/*Temporary store read string		*/
	char* temp, *tok;

	char** parsed_data = malloc(sizeof(char*)*6);

	for(int i = 0; i < num_of_lines; i++){
		line = NULL;				/*No space to store string 		*/
		size = 0;					/*0 size of non-existing string */
		getline(&line, &size, fp);	/*Read line by line 			*/
		
		for(int j = 0; j < 2; j++){
			tok = strtok(temp, ":");
			printf("%s \n", tok);
			parsed_data[i] = strtok(temp, ":");
		}

		for(int i = 0; i < 3; i++)
			args[i] = (unsigned char*)strtok(line, ",");	/*Parse data with respect to delim character*/
		line = NULL;

		free(temp);	
	}
	for(int i = 0; i < 6; i++)
		free(parsed_data[i]);

	free(parsed_data);
	fclose(fp);
	

	return 0;
}
/*---------- End of Main function ----------------*/