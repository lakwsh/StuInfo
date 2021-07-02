#include "score.h"

score::score(school *sch){
	setNo();
	stringstream sql;
	sql<<"SELECT TRUE FROM `student` WHERE `No`="<<no<<" AND `School`="<<sch;
	MYSQL_ROW *rows;
	unsigned int fields;
	if(!query(sql.str(), rows, fields) || !rows) throw exception("student no not exists");
	free(rows);
}
bool score::remove(unsigned int id){
	stringstream sql;
	sql<<"DELETE FROM `score` WHERE `Id`="<<id<<" AND `No`="<<no;
	return query(sql.str());
}
score *score::getScore(unsigned int sch){
	switch(sch){
		case Primary: return new PrimSch;
		case Secondary: return new SecoSch;
		case University: return new UnivSch;
	}
	throw exception("invalid school type");
}

bool PrimSch::insert(){
	cout<<"请输入语文 & 数学 & 英语成绩: ";
	float chi,math,eng;
	cin>>chi>>math>>eng;
	stringstream sql;
	sql<<"INSERT INTO `score` (`No`,`Chi`,`Math`,`Eng`,`Type`) VALUES ("<<no<<","<<chi<<","<<math<<","<<eng<<","<<Primary<<")";
	return query(sql.str());
}
bool SecoSch::insert(){
	PrimSch::insert();
	cout<<"请输入物理 & 化学 & 生物成绩: ";
	float phy,chem,bio;
	cin>>phy>>chem>>bio;
	stringstream sql;
	sql<<"INSERT INTO `score` (`No`,`Phy`,`Chem`,`Bio`,`Type`) VALUES ("<<no<<","<<phy<<","<<chem<<","<<bio<<","<<Secondary<<")";
	return query(sql.str());
}
bool UnivSch::insert(){
	cout<<"请输入课程编号 & 学分: ";
	int lesson;
	float got;
	cin>>lesson>>got;
	stringstream sql;
	sql<<"INSERT INTO `score` (`No`,`Total`,`Got`,`Type`) VALUES ("<<no<<","<<lesson<<","<<got<<","<<University<<")";
	return query(sql.str());
}
void PrimSch::print(my_ulonglong count, MYSQL_ROW *&rows){
	if(!rows){
		cout<<"未查询到相关信息"<<endl;
		return;
	}
	cout<<"编号\t语文\t数学\t英语"<<endl;
	for(int i = 0; i<count; i++) cout<<rows[i][0]<<"\t"<<rows[i][1]<<"\t"<<rows[i][2]<<"\t"<<rows[i][3]<<endl;
	free(rows); // malloc
}
void PrimSch::list(){
	stringstream sql;
	sql<<"SELECT `Id`,`Chi`,`Math`,`Eng` FROM `score` WHERE `Type`="<<Primary<<" AND `No`="<<no;
	MYSQL_ROW *rows;
	unsigned int fields;
	PrimSch::print(query(sql.str(), rows, fields), rows);
}
void SecoSch::print(my_ulonglong count, MYSQL_ROW *&rows){
	if(!rows){
		cout<<"未查询到相关信息"<<endl;
		return;
	}
	cout<<"编号\t物理\t化学\t生物"<<endl;
	for(int i = 0; i<count; i++) cout<<rows[i][0]<<"\t"<<rows[i][1]<<"\t"<<rows[i][2]<<"\t"<<rows[i][3]<<endl;
	free(rows); // malloc
}
void SecoSch::list(){
	PrimSch::list();
	stringstream sql;
	sql<<"SELECT `Id`,`Phy`,`Chem`,`Bio` FROM `score` WHERE `Type`="<<Secondary<<" AND `No`="<<no;
	MYSQL_ROW *rows;
	unsigned int fields;
	SecoSch::print(query(sql.str(), rows, fields), rows);
}
void UnivSch::print(my_ulonglong count, MYSQL_ROW *&rows){
	if(!rows){
		cout<<"未查询到相关信息"<<endl;
		return;
	}
	cout<<"编号\t课号\t\t学分"<<endl;
	for(int i = 0; i<count; i++) cout<<rows[i][0]<<"\t"<<rows[i][1]<<"\t"<<rows[i][2]<<endl;
	free(rows); // malloc
}
void UnivSch::list(){
	stringstream sql;
	sql<<"SELECT `Id`,`Lesson`,`Got` FROM `score` WHERE `Type`="<<University<<" AND `No`="<<no;
	MYSQL_ROW *rows;
	unsigned int fields;
	UnivSch::print(query(sql.str(), rows, fields), rows);
}