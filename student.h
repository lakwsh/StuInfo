#pragma once
#include "database.h"
#include "date.h"
#include <sstream>
#include "school.h"

enum sex_t{
	Male,
	Female
};
class student:public stdno{
private:
	static const char *getSex(sex_t sex);

	void print(my_ulonglong count, MYSQL_ROW *&rows);
public:
	static school *getSchool(unsigned int sch);

	bool insert(char name[16], sex_t sex, date born, school *sch);
	bool edit(char name[16]);
	bool edit(sex_t sex);
	bool edit(date born);
	bool edit(school *sch);

	void listAll();
	void search();
	void search(date d);
	bool remove();
	unsigned int count();
};