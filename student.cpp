#include "student.h"

const char *student::getSex(sex_t sex){
	switch(sex){
		case Male: return "男";
		case Female: return "女";
	}
	return "未定义";
}
school *student::getSchool(unsigned int sch){
	switch(sch){
		case Primary: return new Prim;
		case Secondary: return new Seco;
		case University: return new Univ;
	}
	return new school;
}

bool student::insert(char name[16], sex_t sex, date born, school *sch){
	stringstream sql;
	sql<<"INSERT INTO `student` (`No`,`Name`,`Sex`,`Born`,`School`) VALUES ("<<no<<",\""<<encode(name)<<"\","<<sex<<","<<born<<","<<sch<<")";
	return query(sql.str());
}
bool student::edit(char name[16]){
	stringstream sql;
	sql<<"UPDATE `student` SET `Name`=\""<<encode(name)<<"\" WHERE `No`="<<no;
	return query(sql.str());
}
bool student::edit(sex_t sex){
	stringstream sql;
	sql<<"UPDATE `student` SET `Sex`=\""<<sex<<"\" WHERE `No`="<<no;
	return query(sql.str());
}
bool student::edit(date born){
	stringstream sql;
	sql<<"UPDATE `student` SET `Born`=\""<<born<<"\" WHERE `No`="<<no;
	return query(sql.str());
}
bool student::edit(school *sch){
	stringstream sql;
	sql<<"UPDATE `student` SET `School`=\""<<sch<<"\" WHERE `No`="<<no;
	return query(sql.str());
}
void student::print(my_ulonglong count, MYSQL_ROW *&rows){
	if(!rows){
		cout<<"未查询到相关信息"<<endl;
		return;
	}
	cout<<"学号\t\t姓名\t性别\t出生日期\t学校类别"<<endl;
	for(unsigned int i = 0; i<count; i++) cout<<rows[i][1]<<"\t"<<rows[i][2]<<"\t"<<getSex((sex_t)atoi(rows[i][3]))<<"\t"<<rows[i][4]<<"\t"<<getSchool(atoi(rows[i][5]))->getName()<<endl;
	cout<<"信息显示完毕"<<endl;
	free(rows); // malloc
}
void student::listAll(){
	MYSQL_ROW *rows;
	unsigned int fields;
	print(query("SELECT * FROM `student`", rows, fields), rows);
}
void student::search(){
	MYSQL_ROW *rows;
	unsigned int fields;
	stringstream sql;
	sql<<"SELECT * FROM `student` WHERE `No`="<<no;
	print(query(sql.str(), rows, fields), rows);
}
void student::search(date d){
	MYSQL_ROW *rows;
	unsigned int fields;
	stringstream sql;
	sql<<"SELECT * FROM `student` WHERE `Born`<"<<d;
	print(query(sql.str(), rows, fields), rows);
}
bool student::remove(){
	stringstream sql;
	sql<<"DELETE FROM `student` WHERE `No`="<<no;
	return query(sql.str());
}
unsigned int student::count(){
	MYSQL_ROW *rows;
	unsigned int fields;
	if(!query("SELECT COUNT(*) FROM `student`", rows, fields)) return 0;
	unsigned int ret = atoi(rows[0][0]);
	free(rows);
	return ret;
}