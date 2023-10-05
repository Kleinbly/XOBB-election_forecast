#include <stdio.h>
#include <stdlib.h>
#include <postgresql/libpq-fe.h>
// Processus de connexion au compte utilisateur et enregistrement de la session de connexion et ses détails.

int login(const char *identifier, const char *password, PGconn *conn)
{
	char *user_id;	//Stocke le user_id récupéré à partir de la requête
	const char *query = "SELECT id, email FROM xobb_user WHERE password_hash = $1";
	const char *paramValues[1];
	paramValues[0] = password;
	PGresult *res = PQexecParams(conn , query , 1, NULL , paramValues, NULL , NULL, 0);
	
	
/* 
Cette requête aboutit uniquement si les identifiants de l'utilisateur existent.

	Cette étape retourne une variable (entière):
=> 1, en cas de réussite d'authentification
=> 0, en cas d'echec d'authentification
*/

	if( PQresultStatus(res) != PGRES_TUPLES_OK)
	{
		fprintf(stderr, "Request failed: %s", PQresultErrorMessage(res));
       		PQclear(res);
        	PQfinish(conn);
        	exit(1);
	}
    	
    	
	
	int num_rows = PQntuples(res);
	int found = 0;
	
	for(int i=0; i<num_rows; i++)
	{
		const char *db_mail = PQgetvalue(res, i ,1);
		if(strcmp(identifier, db_mail) == 0)
		{
			found = 1;
			user_id = PQgetvalue(res, i ,0);
			break;
		}
	}
	
	PQclear(res);
	
//Enregistrement de la tentative de connexion après l'étape d'authentififcation et les détails supplémentaires
	const char *paramValues0[2];
	char* success = "SUCCESS";
	if(found ==1){
		char* log_query1 = "INSERT INTO log_session(user_id, attempt_status) VALUES($1, $2) ON CONFLICT DO NOTHING";
		paramValues0[0] = user_id;
		paramValues0[1] = success;
		res = PQexecParams(conn, log_query1, 2, NULL, paramValues0 , NULL, NULL, 0);
	}
	
	if(found ==0){
		char* log_query2 = "INSERT INTO log_session(failed_attempt_email_input) VALUES($1)";
		paramValues[0] = identifier;
		res = PQexecParams(conn, log_query2, 1, NULL, paramValues , NULL, NULL, 0);
	}
		
	if( PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		fprintf(stderr, "Request failed: %s", PQresultErrorMessage(res));
       		PQclear(res);
        	PQfinish(conn);
        	exit(1);
	}
	PQclear(res);
	
	
//Changement du statut de connexion de l'utilisateur(status_connect) à TRUE
	if(found == 1){
		const char *id_query = "SELECT id FROM log_session WHERE user_id = $1 AND attempt_status = $2 ORDER BY attempt_timestamp DESC LIMIT 1";
		char* success = "SUCCESS";
		const char *paramValues2[2];
		paramValues2[0] = user_id;
		paramValues2[1] = success;
		res = PQexecParams(conn, id_query, 2, NULL, paramValues2 , NULL, NULL, 0);
		const char* current_log_session_id = PQgetvalue(res, 0 ,0);
		
		if( PQresultStatus(res) != PGRES_TUPLES_OK){
			fprintf(stderr, "Request failed: %s", PQresultErrorMessage(res));
       			PQclear(res);
        		PQfinish(conn);
        		exit(1);
		}
	PQclear(res);
	
		const char *updateQuery = "UPDATE xobb_user SET status_connected = TRUE, current_log_session_id = $1 WHERE id = $2";
		paramValues0[1] = user_id;
		paramValues0[0] = current_log_session_id;
		res = PQexecParams(conn, updateQuery, 2, NULL, paramValues0 , NULL, NULL, 0);
	
		if( PQresultStatus(res) != PGRES_COMMAND_OK){
			fprintf(stderr, "Request failed: %s", PQresultErrorMessage(res));
       			PQclear(res);
        		PQfinish(conn);
        		exit(1);
		}
		PQclear(res);
	}
	
	
	return found;
}
