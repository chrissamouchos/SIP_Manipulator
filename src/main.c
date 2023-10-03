/*---------- Start of System Libraries ------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sqlite3.h> /*Include SQLite library*/
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
    while ((c = getopt(argc, argv, "i:")) != -1) {
        switch (c) {
            case 'i':
                input_file = optarg;
                break;
            case '?':
                return 1;
        }
    }
    /*---------------End of Options Parsing----------------*/

    if (!input_file) { /*Check if the input file is not given, print error, terminate*/
        printf("Input file is mandatory, none was given\n");
        return 1;
    }

    size_t size;
    char** data_array = malloc(sizeof(char*) * 9);

    FILE* fp = fopen(input_file, "r"); /*Open the input file to parse its data*/

    DB db = create_db("myDB");         /*Create or open db 	*/
    int r = create_SIP_table(db);      /*Create SIP table 	*/

    if (db == NULL || r < 0) 			/*Sanity Check 		*/
        return -1;

    int index = -1;
    char* line = NULL;

    while (getline(&line, &size, fp) != -1) {
        index++;
        /*Split the line using ':' delimiter*/
        char* token = strtok(line, ":");

        if (token != NULL) {
            /*Extract the second string (token)*/
            token = strtok(NULL, ":");

            if (token != NULL) {
                /*Remove leading and trailing spaces from the extracted string*/
                char* start = token;
                while (*start && (*start == ' ' || *start == '\t' || *start == '\n')) {
                    start++;
                }

                char* end = start + strlen(start) - 1;
                while (end > start && (*end == ' ' || *end == '\t' || *end == '\n')) {
                    end--;
                }
                end[1] = '\0'; /*Null-terminate the string*/

                if (index < 9)
                    data_array[index] = strdup(start);
            }
        }
    }

    if(insert_into_SIP(db, data_array) < 0)
    	return -1;

    /*Close the file and free allocated memory*/
    fclose(fp);

    if (line)
        free(line);

    sqlite3_close(db); /*Close the db connection*/

    for (int i = 0; i < 9; i++)
        free(data_array[i]);

    free(data_array);
    printf("Free all allocated memory...\n");

    return 0;
}
/*---------- End of Main function ----------------*/
