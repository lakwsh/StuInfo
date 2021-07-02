#include "score.h"
#include "school.h"

bool score::remove(unsigned int id){
	stringstream sql;
	sql<<"DELETE FROM `score` WHERE `Id`="<<id;
	return query(sql.str());
}
score *score::getScore(unsigned int sch){
	switch(sch){
		case Primary: return new PrimSch;
		case Secondary: return new SencSch;
		case University: return new UnivSch;
	}
	throw exception("invalid school type");
}

bool PrimSch::insert(){
	cout<<"请输入语文 & 数学 & 英语成绩: ";
	float chi,math,eng;
	cin>>chi>>math>>eng;
	stringstream sql;
	sql<<"INSERT INTO `score` (`No`,`Chi`,`Math`,`Eng`) VALUES ("<<no<<","<<chi<<","<<math<<","<<eng<<")";
	return query(sql.str());
}
bool SencSch::insert(){
	PrimSch::insert();
	cout<<"请输入物理 & 化学 & 生物成绩: ";
	float phy,chem,bio;
	cin>>phy>>chem>>bio;
	stringstream sql;
	sql<<"INSERT INTO `score` (`No`,`Phy`,`Chem`,`Bio`) VALUES ("<<no<<","<<phy<<","<<chem<<","<<bio<<")";
	return query(sql.str());
}
bool UnivSch::insert(){
	cout<<"请输入课程编号 & 学分: ";
	int lesson;
	float got;
	cin>>lesson>>got;
	stringstream sql;
	sql<<"INSERT INTO `score` (`No`,`Total`,`Got`) VALUES ("<<no<<","<<lesson<<","<<got<<")";
	return query(sql.str());
}
void PrimSch::print(my_ulonglong count, MYSQL_ROW *&rows){
	if(!rows){
		cout<<"未查询到相关信息"<<endl;
		return;
	}
	cout<<"编号\t语文\t数学\t英语"<<endl;
	cout<<rows[0][0]<<"\t"<<rows[0][1]<<"\t"<<rows[0][2]<<"\t"<<rows[0][3]<<endl;
	free(rows); // malloc
}
void PrimSch::list(){
	MYSQL_ROW *rows;
	unsigned int fields;
	print(query("SELECT `Id`,`Chi`,`Math`,`Eng` FROM `score`", rows, fields), rows);
}
void SencSch::print(my_ulonglong count, MYSQL_ROW *&rows){
	if(!rows){
		cout<<"未查询到相关信息"<<endl;
		return;
	}
	cout<<"编号\t物理\t化学\t生物"<<endl;
	cout<<rows[0][0]<<"\t"<<rows[0][1]<<"\t"<<rows[0][2]<<"\t"<<rows[0][3]<<endl;
	free(rows); // malloc
}
void SencSch::list(){
	PrimSch::list();
	MYSQL_ROW *rows;
	unsigned int fields;
	print(query("SELECT `Id`,`Phy`,`Chem`,`Bio` FROM `score`", rows, fields), rows);
}
void UnivSch::print(my_ulonglong count, MYSQL_ROW *&rows){
	if(!rows){
		cout<<"未查询到相关信息"<<endl;
		return;
	}
	cout<<"编号\t课号\t\t学分"<<endl;
	cout<<rows[0][0]<<"\t"<<rows[0][1]<<"\t"<<rows[0][2]<<endl;
	free(rows); // malloc
}
void UnivSch::list(){
	MYSQL_ROW *rows;
	unsigned int fields;
	print(query("SELECT `Id`,`Lesson`,`Got` FROM `score`", rows, fields), rows);
}