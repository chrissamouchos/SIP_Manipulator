/*File that contains the prototypes of various functions*/
#pragma once	/*Include only once*/

#include <sqlite3.h>

void red();		/*Chane printing color to red 	*/

void green();	/*Chane printing color to green	*/

void reset();	/*Reset color to default		*/

int line_counter(char* input); /*Count lines of given file 					*/

/*-------------------- DB Stuff ----------------------------*/

typedef sqlite3* DB;

DB create_db(char* name);	/*Create in current directory name.DB 	*/

int create_SIP_table(DB myDB);	/*execute specific create table 	*/

int insert_into_SIP(DB myDB, char** data_array);

void select_all(DB myDB);
/*-------------------- End of DB ---------------------------*/