#pragma once
#include <iostream>
using namespace std;

enum school_t{
	Undefined,
	Primary,
	Secondary,
	University
};
class school{
protected:
	virtual unsigned int getValue(){ return Undefined; }
public:
	virtual const char *getName(){ return "未定义"; }
	friend ostream &operator<<(ostream &os, school *sc){
		os<<sc->getValue();
		return os;
	}
};

class Prim:public school{
protected:
	unsigned int getValue() override{ return Primary; }
public:
	const char *getName() override{ return "小学"; }
};
class Seco:public school{
protected:
	unsigned int getValue() override{ return Secondary; }
public:
	const char *getName() override{ return "中学"; }
};
class Univ:public school{
protected:
	unsigned int getValue() override{ return University; }
public:
	const char *getName() override{ return "大学"; }
};