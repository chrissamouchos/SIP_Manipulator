/*File that contains the prototypes of various functions*/
#pragma once	/*Include only once*/

#include <sqlite3.h>

int line_counter(char* input); /*Count lines of given file 					*/

/*-------------------- DB Stuff ----------------------------*/

typedef sqlite3* DB;

DB create_db(char* name);	/*Create in current directory name.DB 	*/

int create_SIP_table(DB myDB);	/*execute specific create table 	*/

int insert_into_SIP(DB myDB, char** data_array);/*Save all data to the db*/

void select_all(DB myDB);	/*Print all data inside the db 			 */
/*-------------------- End of DB ---------------------------*/