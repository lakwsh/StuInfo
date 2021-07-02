#pragma once
#include "database.h"
#include <sstream>
using namespace std;

class score:protected stdno{
private:
	virtual void print(my_ulonglong count, MYSQL_ROW *&rows) = 0; // ´¿Ðéº¯Êý
public:
	score(){ setNo(); }
	static score *getScore(unsigned int school);

	virtual bool insert() = 0;
	virtual void list() = 0;
	virtual bool remove(unsigned int id);
};

class PrimSch:public score{
private:
	void print(my_ulonglong count, MYSQL_ROW *&rows);
public:
	bool insert();
	void list();
};
class SencSch:public PrimSch{
private:
	void print(my_ulonglong count, MYSQL_ROW *&rows);
public:
	bool insert();
	void list();
};
class UnivSch:public score{
private:
	void print(my_ulonglong count, MYSQL_ROW *&rows);
public:
	bool insert();
	void list();
};