/*File that contains the prototypes of various functions*/
#pragma once	/*Include only once*/

#include <sqlite3.h>

void red();		/*Chane printing color to red 	*/

void green();	/*Chane printing color to green	*/

void reset();	/*Reset color to default		*/

int line_counter(char* input); /*Count lines of given file*/

/*-------------------- DB Stuff ----------------------------*/

typedef sqlite3* DB;

DB create_db(char* name);
/*-------------------- End of DB ---------------------------*/