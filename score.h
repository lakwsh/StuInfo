#pragma once
#include "database.h"
#include "school.h"
#include <sstream>
using namespace std;

class score:protected stdno{
private:
	void print(my_ulonglong count, MYSQL_ROW *&rows){ }
public:
	score(school *sch);
	static score *getScore(unsigned int sch);

	virtual bool insert() = 0;
	virtual void list() = 0;
	virtual bool remove(unsigned int id);
};

class PrimSch:virtual public score{
private:
	void print(my_ulonglong count, MYSQL_ROW *&rows); // ÖØÐ´Òþ²Ø
public:
	PrimSch():score(new Prim){ }
	bool insert() override;
	void list() override;
};
class SecoSch:public PrimSch{
private:
	void print(my_ulonglong count, MYSQL_ROW *&rows);
public:
	SecoSch():score(new Seco){ }
	bool insert() override;
	void list() override;
};
class UnivSch:virtual public score{
private:
	void print(my_ulonglong count, MYSQL_ROW *&rows);
public:
	UnivSch():score(new Univ){ }
	bool insert() override;
	void list() override;
};