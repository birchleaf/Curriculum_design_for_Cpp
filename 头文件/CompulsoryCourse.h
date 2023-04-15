#pragma once
#include <iostream>
using namespace std;
#include "Course.h"

//继承抽象类Course
class Compulsory : public Course
{
public:
	//构造函数，实现对象的初始化，用来添加或读取课程信息用
	Compulsory(long num , string name, string stime, string score, string term,  int PeopleCount = 0,string kind = "必修课");
	//重写虚函数
	virtual void PrintCourse();		//显示课程信息
	
private:
	//私有，防止其他函数调用
	virtual void PrintStudent();	//输出已报名学生信息
};