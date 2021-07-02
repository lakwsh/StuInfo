#include "database.h"

// https://dev.mysql.com/doc/c-api/5.7/en/c-api-function-reference.html

database::database(){
	mysql_init(&db);
	if(!mysql_real_connect(&db, "vps.lakwsh.net", "stuinfo", "xj8Wq4TZ", "stuinfo", 3306, NULL, 0)){
		cout<<"Failed to connect to database. Error: "<<mysql_error(&db)<<endl;
		throw exception("database init error.");
	}
    mysql_set_character_set(&db, "utf8");
}
database::~database(){
	mysql_close(&db);
}
char *database::encode(const char *str){
    unsigned long len = strlen(str);
    char *result = (char *)malloc(len*2+1);
    if(!result) throw exception("malloc failed.");
    if(mysql_real_escape_string(&db, result, str, len)==-1) return NULL;
    return result;
}
bool database::query(string sql){
    return !mysql_query(&db, sql.c_str());
}
my_ulonglong database::query(string sql, MYSQL_ROW *&res, unsigned int &fields){
    if(query(sql)){
        MYSQL_RES *result = mysql_store_result(&db);
        if(result){
            fields = mysql_num_fields(result);
            my_ulonglong num_rows = mysql_num_rows(result);
            if(num_rows>0){
                if(!(res = (MYSQL_ROW *)malloc(sizeof(MYSQL_ROW)*num_rows))) throw exception("malloc failed.");
                for(unsigned int i = 0; i<num_rows; i++) res[i] = mysql_fetch_row(result);
                mysql_free_result(result);
                return num_rows;
            }
        }
    }
    return 0;
}