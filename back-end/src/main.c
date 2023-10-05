#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <postgresql/libpq-fe.h>
#include "../include/login.h"

const char *conninfo = "dbname=postgres user=klein password=12345  hostaddr=127.0.0.1 ";
PGconn *conn;

int main(int argc, char *argv[]){
	
	//Connexion à la base de données
	conn = PQconnectdb(conninfo);
    	if (PQstatus(conn) != CONNECTION_OK) {
        	fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
        	PQfinish(conn);
        	exit(1);
    	}
    	
	login("billy", "klein",conn);
	return 0;

}
