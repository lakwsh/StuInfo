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
	virtual char *encode(const char *str) final; // ��ֹ����
	virtual bool query(string sql) final;
	virtual my_ulonglong query(string sql, MYSQL_ROW *&res, unsigned int &fields) final; // ��������
private:
	MYSQL db;
};

typedef unsigned int sno;
class stdno:virtual protected database{
protected:
	sno no;
public:
	void setNo(){ cout<<"������ѧ��: "; cin>>no; }
};