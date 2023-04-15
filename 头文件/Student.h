#pragma once
#include <iostream>
#include "Course.h"
#include <fstream>
#include <string>
#include "CompulsoryCourse.h"
#include "OptionalCourse.h"
#include "CheckInput.h"
#define FILE "Course.txt"
using namespace std;

class Student
{
public:
	int Count;								//课程数量
	Course** COURSE;						//定义一个指向指针数组的父类指针COURSE,便于维护子类
	Student();
	int StuCourseCount();					//读取课程数量
	void StuPrintCourse();					//输出所有课程信息
	void StuReadFile();						//读取文件
	long StuSearch(int num);	//查询课程信息
	void StuAdd(int num, long StuID, string StuName, string StuSex, string StuYear, string StuDepartment, string StuClass, string StuContact);	//选课（添加学生）
	void Studel(int num, long StuID);			//退课（删除学生）
	void HaveCourse(long StuID);		//查询已选的课程
	void StuSaveFile();						//保存
	void StuOpration(long StuID,string StuName , string StuSex, string StuYear ,string StuDepartment ,string StuClass , string StuContact);	//操作
	bool CheckStudent(long StuID);
	struct STUDENT* GetTheStudent(long StuID);	//检索并返回学生信息结构体
	~Student();
};
