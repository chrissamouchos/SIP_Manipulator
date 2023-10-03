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

	if(!input_file){ /*Check if input file is not given, print error, terminate*/
		printf("Input file is mandatory, none was given\n");
		return 1;
	}

	// size_t size;
	// char** args = NULL;
	// char * token, *line, *start, *end = NULL;

	// int num_of_lines = line_counter(input_file);
	// FILE* fp = fopen(input_file, "r"); 	/*Open input file to parse it's data*/
	 
	// while (getline(&line, &size, fp) != -1) {
	// // Split the line using ':' delimiter
	// 	token = strtok(line, ":");
        
    //     if (token != NULL) {
    //         // Extract the second string (token)
    //         token = strtok(NULL, ":");
    //         if (token != NULL) {

    //             // Remove leading and trailing spaces from the extracted string
    //             start = token;

    //             while (*start && (*start == ' ' || *start == '\t' || *start == '\n')){
    //                 start++;
    //             }

    //             end = start + strlen(start) - 1;

    //             while (end > start && (*end == ' ' || *end == '\t' || *end == '\n')) {
    //                 end--;
    //             }

    //             end[1] = '\0'; // Null-terminate the string
    //             printf("%s\n", start);
    //         }
    //     }
    // }

    // // Close the file and free allocated memory
    // fclose(fp);

    // if (line) {
    //     free(line);
    // }
	
    DB db = create_db("myDB");

    sqlite3_close(db);

	return 0;
}
/*---------- End of Main function ----------------*/