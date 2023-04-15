#include "OptionalCourse.h"

Optional::Optional(long num, string name, string stime, string score, string term, int PeopleCount,string kind)
{
	this->num = num;                
	this->name = name;          
	this->kind = "选修课";           
	this->stime = stime;               
	this->score = score;               
	this->term = term;                
	this->PeopleCount = PeopleCount;
	this->Student[MAX];
}
void Optional::PrintCourse()
{

	cout << endl;
	cout << "-------------------------------------------------------------------------" << endl;
	cout << "课程信息: " << endl;
	cout << "编号" << '\t';
	cout << "名称" << '\t';
	cout << "性质" << '\t';
	cout << "学时" << '\t';
	cout << "学分" << '\t';
	cout << "学期" << '\t'<<'\t';
	cout << "人数" << endl;
	cout << this->num << '\t';
	cout << this->name << '\t';
	cout << this->kind << '\t';
	cout << this->stime << '\t';
	cout << this->score << '\t';
	cout << this->term << '\t';
	cout << this->PeopleCount << endl;

}


void Optional::PrintStudent()
{
	for (int i = 0; i < this->PeopleCount; i++)
	{
		cout << endl;
		cout << "学生信息: " << endl;
		cout << "学号" << '\t';
		cout << "姓名" << '\t';
		cout << "性别" << '\t';
		cout << "年龄" << '\t';
		cout <<"系别" << '\t';
		cout <<  "班级" << '\t';
		cout << "联系方式"  << endl;
		cout << this->Student[i].StuID << '\t';
		cout << this->Student[i].StuName << '\t';
		cout << this->Student[i].StuSex << '\t';
		cout << this->Student[i].StuYear << '\t';
		cout << this->Student[i].StuDepartment << '\t';
		cout << this->Student[i].StuClass << '\t';
		cout << this->Student[i].StuContact << endl;
	}
	cout << "-------------------------------------------------------------------------" << endl;

}