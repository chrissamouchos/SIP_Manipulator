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
	fprintf(stdout, "%s.db created successfully\n",name);
	return myDB;
}

int create_SIP_table(DB myDB){
	char* errMsg = NULL;
	int rc;

	const char* createTableSQL = 
        "CREATE TABLE IF NOT EXISTS SIP_MESSAGE ("
        "	id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "	Type TEXT,"
        "	Via TEXT,"
        "	`From` TEXT,"
        "	`To` TEXT,"
        " 	Call_ID TEXT,"
        " 	CSeq TEXT,"
        " 	Max_Forwards TEXT,"
        " 	Content_Type TEXT,"
        " 	Content_Length TEXT);" ;

    // Execute the SQL statement to create the table
    rc = sqlite3_exec(myDB, createTableSQL, 0, 0, &errMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errMsg);
        sqlite3_free(errMsg);
        return -1;
    }
    else {
    	fprintf(stdout, "Table created successfully\n");
        return 0;
	}
}

int insert_into_SIP(DB myDB, char** data_array){
	const char* insert_sql = "INSERT INTO SIP_MESSAGE(Type, Via, `To`, `From`, Call_ID, CSeq, Max_Forwards, Content_Type, Content_Length) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)";

	sqlite3_stmt* stmt;

	if (sqlite3_prepare_v2(myDB, insert_sql, -1, &stmt, NULL) != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(myDB));
		return -1;
	}

	/*Bind the parameter*/
	for(int i = 1; i <= 9; i++)
		sqlite3_bind_text(stmt, i, data_array[i-1], -1, SQLITE_STATIC);
	
	/*Execute the statement*/
	if (sqlite3_step(stmt) != SQLITE_DONE) {
		fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(myDB));
		return -1;
	}

	sqlite3_finalize(stmt); /*When you're done with a prepared statement and want to release associated resources*/
	return 0;
}