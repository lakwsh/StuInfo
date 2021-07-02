#include "date.h"

int date::Days(){
	if(isBad(mm, month)) throw out_of_range("invalid days");
	static int dpm[12] = {31,-1,31,30,31,30,31,31,30,31,30,31};
	return month==2?isLeap()?29:28:dpm[month-1];
}
bool date::isBad(type t, int c){
	switch(t){
		case yy: return c<0 || c>9999;
		case mm: return c<1 || c>12;
		case dd: return c<1 || c>Days();
		case ds: return c<1;
	}
	return true;
}