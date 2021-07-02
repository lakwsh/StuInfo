#pragma once
#include <iomanip>
using namespace std;

class date{
	enum type{yy, mm, dd, ds};
private:
	int year;
	int month;
	int day;
	bool isLeap(){ return !(year%400) || !(year%4)&&year%100; }
	int Days();
	bool isBad(type t, int c);
	bool check(){ return isBad(yy, year) || isBad(mm, month) || isBad(dd, day);	}
public:
	friend istream &operator>>(istream &is, date &d){
		char buf[9] = {0};
		is>>buf;
		d.day = atoi(buf+6);
		*(buf+6) = 0;
		d.month = atoi(buf+4);
		*(buf+4) = 0;
		d.year=atoi(buf);
		if(d.check()) throw invalid_argument("invalid date");
		return is;
	}
	friend ostream &operator<<(ostream &os, date d){
		os<<d.year<<setw(2)<<setfill('0')<<d.month<<setw(2)<<setfill('0')<<d.day;
		return os;
	}
};