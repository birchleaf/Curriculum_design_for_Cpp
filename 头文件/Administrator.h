#pragma once
#include <iostream>
#include "Course.h"
#include <fstream>
#include <string>
#include <list>
#include "CheckInput.h"
#include "CompulsoryCourse.h"
#include "OptionalCourse.h"
#define FILE "Course.txt"
using namespace std;
 
class Administrator
{	


public:
	int Count ;						//系统内总课程数，初始化为0
	int PeoCou;						//系统内学生总人数
	Course** COURSE;				//定义一个指向指针数组的父类指针COURSE,便于维护子类
	list <STUDENT> StuList;			//创建链表，储存学生信息
	Administrator();				//构造函数
	int CourseCount();				//初始化读取课程数量
	void ReadFile();				//初始化读取文件
	void PrintAll();				//输出课程信息和学生学号
	int ReadStuList();				//读取学生信息
	void ShowStudent(const list <STUDENT>&StuList); //输出学生信息
	long Search(int num);			//查询课程
	void Search(long StuID, const list <STUDENT>& StuList); //查询学生信息
	void Add();						//添加课程
	void Add(int num, long StuID);	//添加学生
	void Change(int x);			//修改课程信息
	void Change(long StuID);  //修改学生
	void del(int x);				//删除课程
	void del(int num, long StuID);		//删除学生
	void SaveFile();				//保存文件
	void Opration();				//管理员操作
	~Administrator();				//析构函数
};

