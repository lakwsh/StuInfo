#pragma once
#include <mysql.h>
#include <string>
#include <iostream>
using namespace std;

class database{
public:
	database();
	virtual ~database();
protected:
	virtual char *encode(const char *str) final; // ½ûÖ¹¸²¸Ç
	virtual bool query(string sql) final;
	virtual my_ulonglong query(string sql, MYSQL_ROW *&res, unsigned int &fields) final; // º¯ÊıÖØÔØ
private:
	MYSQL db;
};

typedef unsigned int sno;
class stdno:virtual protected database{
protected:
	sno no;
public:
	void setNo(){ cout<<"ÇëÊäÈëÑ§ºÅ: "; cin>>no; }
};