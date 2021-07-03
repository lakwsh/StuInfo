#pragma once
#include "database.h"
#include "school.h"
#include <sstream>
using namespace std;

class score:protected stdno{
private:
	virtual void print(my_ulonglong count, MYSQL_ROW *&rows) = 0; // ���麯��
public:
	score(school *sch);
	static score *getScore(unsigned int sch);

	virtual bool insert() = 0;
	virtual void list() = 0;
	virtual bool remove(unsigned int id);
};

class PrimSch:virtual public score{
private:
	void print(my_ulonglong count, MYSQL_ROW *&rows) override;
public:
	PrimSch():score(new Prim){ }
	bool insert() override;
	void list() override;
};
class SecoSch:public PrimSch{
private:
	void print(my_ulonglong count, MYSQL_ROW *&rows) override;
public:
	SecoSch():score(new Seco){ }
	bool insert() override;
	void list() override;
};
class UnivSch:virtual public score{
private:
	void print(my_ulonglong count, MYSQL_ROW *&rows) override;
public:
	UnivSch():score(new Univ){ }
	bool insert() override;
	void list() override;
};