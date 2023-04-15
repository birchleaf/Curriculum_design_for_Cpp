#pragma once
#include <iostream>
#define MAX 50 //每门课学生最大人数

using namespace std;



struct STUDENT
{
	long StuID;		//学号
	string StuName;	//姓名
	string StuSex;	//性别
	string StuYear;	//年龄
	string StuDepartment;	//系别
	string StuClass;	//班级
	string StuContact;	//联系方式
};


class Course	//创建课程抽象类
{
	//声明友元函数，使得只有管理员能输出学生信息
	friend class Administrator;
	friend class Compulsory;
	friend class Optional;

public:
		//定义一个抽象类Course，派生出必修课（Compulsory）和选修课（Optional）两大类，用上多态的性质
		virtual void PrintCourse()=0;		//输出基本课程信息
		long num;							//课程编号   
		string name;						//课程名称   
		string kind;						//课程性质:必修或选修  
		string stime;							//总学时   
		string score;							//学分    
		string term;							//开课学期   
		int PeopleCount;					//已报名人数						
		STUDENT Student[MAX];				//已报名该课程的学生信息
private:		
	//私有，防止其他函数调用
	virtual void PrintStudent() = 0;
};