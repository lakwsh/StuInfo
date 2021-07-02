#include "student.h"
#include "score.h"

class menu{
public:
    static void first(){
        cout<<"1. 学生信息管理"<<endl;
        cout<<"2. 学生成绩管理"<<endl;
        cout<<"3.退出系统"<<endl;
    }
    static void information(){
        cout<<"1. 学生信息录入"<<endl;
        cout<<"2. 学生信息查询"<<endl;
        cout<<"3. 学生信息列表"<<endl;
        cout<<"4. 学生信息修改"<<endl;
        cout<<"5. 学生信息删除"<<endl;
        cout<<"6. 查询总记录数"<<endl;
        cout<<"7. 按出生日期筛选"<<endl;
        cout<<"8. 返回上一页"<<endl;
    }
    static void achievement(){
        cout<<"1. 学生成绩录入"<<endl;
        cout<<"2. 学生成绩列表"<<endl;
        cout<<"3. 学生成绩删除"<<endl;
        cout<<"4. 返回上一页"<<endl;
    }
    static unsigned int school(){
        cout<<"请选择学校类别: "<<endl;
        cout<<"1. 小学"<<endl;
        cout<<"2. 中学"<<endl;
        cout<<"3. 大学"<<endl;
        unsigned int sch;
        cin>>sch;
        return sch;
    }
    static void sex(){
        cout<<"1. 男"<<endl;
        cout<<"2. 女"<<endl;
    }
    static void info_edit(){
        cout<<"1. 修改姓名"<<endl;
        cout<<"2. 修改性别"<<endl;
        cout<<"3. 修改出生日期"<<endl;
        cout<<"4. 修改学生类型"<<endl;
        cout<<"5. 返回上一页"<<endl;
    }
    static void getc(unsigned int &c){
        cin>>c;
        system("cls");
    }
};
int main(){
    unsigned int c;
    while(true){
        menu::first();
        menu::getc(c);
        switch(c){
            case 1:
            {
                student stu;
                while(true){
                    menu::information();
                    menu::getc(c);
                    try{
                        switch(c){
                            case 1:
                            {
                                stu.setNo();
                                cout<<"请输入姓名 & 性别(0=男,1=女) & 出生日期(如19871231): ";
                                char name[16];
                                bool sex;
                                date d;
                                cin>>name>>sex>>d;
                                if(stu.insert(name, (sex_t)sex, d, stu.getSchool(menu::school()))) cout<<"录入成功"<<endl;
                                else cout<<"录入失败!!! 请检查学号是否重复"<<endl;
                                break;
                            }
                            case 2: stu.setNo(); stu.search(); break;
                            case 3: stu.listAll(); break;
                            case 4:
                            {
                                stu.setNo();
                                while(true){
                                    menu::info_edit();
                                    menu::getc(c);
                                    switch(c){
                                        case 1:
                                            char name[16];
                                            cout<<"请输入姓名: ";
                                            cin>>name;
                                            stu.edit(name);
                                            break;
                                        case 2:
                                            bool sex;
                                            cout<<"请输入性别(0=男,1=女): ";
                                            cin>>sex;
                                            stu.edit((sex_t)sex);
                                            break;
                                        case 3:
                                            date d;
                                            cout<<"请输入出生日期: ";
                                            cin>>d;
                                            stu.edit(d);
                                            break;
                                        case 4: stu.edit(stu.getSchool(menu::school())); break;
                                        case 5: goto info_edit_out;
                                    }
                                    cout<<endl;
                                }
                            info_edit_out:
                                break;
                            }
                            case 5: stu.setNo(); if(stu.remove()){ cout<<"删除成功"<<endl; } break;
                            case 6: cout<<"记录条数: "<<stu.count()<<endl; break;
                            case 7:
                            {
                                cout<<"请输入出生日期,将显示所有出生日期小于该值的学生: ";
                                date d;
                                cin>>d;
                                stu.search(d);
                                break;
                            }
                            case 8: goto info_out;
                        }
                        cout<<endl;
                    }catch(exception e){
                        cout<<"异常: "<<e.what()<<endl<<endl;
                    }
                }
            info_out:
                break;
            }
            case 2:
            {
                try{
                    score *sc = score::getScore(menu::school());
                    while(true){
                        menu::achievement();
                        menu::getc(c);
                        switch(c){
                            case 1: if(sc->insert()){ cout<<"录入成功"<<endl; } break;
                            case 2: sc->list(); break;
                            case 3:
                            {
                                cout<<"请输入记录编号: ";
                                unsigned int id;
                                cin>>id;
                                if(sc->remove(id)) cout<<"删除成功"<<endl;
                                break;
                            }
                            case 4: goto achi_out;
                        }
                        cout<<endl;
                    }
                }catch(exception e){
                    cout<<"异常: "<<e.what()<<endl<<endl;
                }
            achi_out:
                break;
            }
            case 3: return 0;
        }
    }
}