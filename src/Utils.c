/*File that contains source code of various functions*/
#include <stdio.h>
#include <string.h>

#include "Utils.h"

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

    /* Execute the SQL statement to create the table */
    rc = sqlite3_exec(myDB, createTableSQL, 0, 0, &errMsg);

    if (rc != SQLITE_OK) {	/* Sanity check */
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

	if (sqlite3_prepare_v2(myDB, insert_sql, -1, &stmt, NULL) != SQLITE_OK) { /* Sanity check */
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

void select_all(DB myDB){
	sqlite3_stmt* stmt;
	const char* select = "SELECT * FROM SIP_MESSAGE;";

	int rc = sqlite3_prepare_v2(myDB, select, -1, &stmt, NULL);
	
	if (rc != SQLITE_OK){
    	fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(myDB));
    	return;
	}

	int id = -1;
	const unsigned char *type, *via, *from, *to, *call_id, *cseq, *max_forwards, *content_type, * content_length;
	
	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    	/*Retrieve data from the current row*/
    	id 				= sqlite3_column_int(stmt, 0);
    	type 			= sqlite3_column_text(stmt, 1);
    	via 			= sqlite3_column_text(stmt, 2);
    	from 			= sqlite3_column_text(stmt, 3);
    	to 				= sqlite3_column_text(stmt, 4);
    	call_id 		= sqlite3_column_text(stmt, 5);
    	cseq 			= sqlite3_column_text(stmt, 6);
    	max_forwards 	= sqlite3_column_text(stmt, 7);
    	content_type 	= sqlite3_column_text(stmt, 8);
    	content_length 	= sqlite3_column_text(stmt, 9);

	   	/* Process or print the retrieved data as needed */
    	printf("ID:%d\nTYPE:%s\nVIA:%sFROM:%sTO:%sCALL_ID:%sCSEQ:%sMAX_FORWARDS:%sCONTENT_TYPE%sCONTENT_LENGTH%s\n", id, type, via, from, to, call_id, cseq, max_forwards, content_type, content_length);
	}

	/*Check for errors or end of data*/
	if (rc != SQLITE_DONE)
    	fprintf(stderr, "Error reading data: %s\n", sqlite3_errmsg(myDB));
	
	sqlite3_finalize(stmt);
	return;
}