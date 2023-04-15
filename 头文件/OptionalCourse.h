#pragma once
#include <iostream>
using namespace std;
#include "Course.h"

//继承抽象类Course
class Optional : public Course
{
public:
	//构造函数，实现对象的初始化，用来添加或读取课程信息用
	Optional(long num, string name, string stime, string score, string term,  int PeopleCount = 0,string kind = "选修课");
	//重写虚函数
	virtual void PrintCourse();
	
private:
	//私有，防止其他函数调用
	virtual void PrintStudent();
};