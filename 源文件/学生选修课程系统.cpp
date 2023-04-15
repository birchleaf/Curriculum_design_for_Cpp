#include <iostream>
#include <string>
#include "CheckInput.h"
#include "Administrator.h"
//#include "Course.h"
#include "Student.h"
#include "Menu.h"           //包含必要头文件
using namespace std;       //使用命名空间


//功能实现
int main()
{
	Menu Meu;          //创建一个菜单对象   
	string ISelect = "-1";	//定义字符串变量ISelect进行身份判定	
	Meu.IndentityMenu();	//显示身份选择界面
loop:cout << "请输入“1”、“2”或“0”以选择你的身份: ";		//loop进行输入错误后的重新输入
	cin >> ISelect;		//输入
	//若用户选择“管理员”身份
	if (ISelect == "1")
	{
		system("cls");
		cout << "***您选择了：1.管理员***" << endl;
		cout << "请输入密码" << endl;
		string PassWard;
		cin >> PassWard;		//输入管理员密码，默认密码设定为：admin
		//若管理员密码输入错误，则重新输入
		while (PassWard != "admin")
		{
			cout << "密码错误，请重新输入！" << endl;
			cin >> PassWard;
		}
		//输入正确，进入管理员界面
		Meu.ShowWelcome("管理员");	//输出“欢迎管理员”文字
		system("pause");
		system("cls");
		Administrator Admin;		//创建Admin（管理员）对象并调用构造函数进行初始化
		while (true)
		{

			Meu.ShowWelcome("管理员");	//输出“欢迎管理员”文字
			Meu.AdmMenu();			//显示管理员菜单界面
			//操作选择函数
			Admin.Opration();		//调用管理员操作

		}

	}
	//选择“学生”身份
	else if (ISelect == "2")
	{
		system("cls");
		cout << "***您选择了：2.学生***" << endl;
		long StuID;			//定义学生学号变量
		string StuName;
		string StuSex;
		string StuYear;
		string StuDepartment;
		string StuClass;
		string StuContact;
		string InPut;		//定义string类，便于进行输入检查
		cout << "请输入您的学号" << endl;
		cin >> InPut;
		//若输入不为正整数，重新输入
		while (!checkint(InPut))
		{
			cout << "请输入正确的学号！" << endl;
			cin >> InPut;
		}

		StuID = strlong(InPut);		//输入成功，string转为long，并赋值到StuID中
		//输入正确，进入学生界面
		Meu.ShowWelcome(StuID);
		system("pause");
		system("cls");
		Student Stu;
		//检索是否已有该学生
		if (!Stu.CheckStudent(StuID)) //若无
		{
			cout << endl;
			cout << "您还未选课，请输入信息，并选择一门课程以保存您的数据" << endl;
			cout << "请输入姓名：";
			cin >> StuName;
			cout << "请输入性别：";
			cin >> StuSex;
			cout << "请输入年龄：";
			cin >> StuYear;
			cout << "请输入系别：";
			cin >> StuDepartment;
			cout << "请输入班级：";
			cin >> StuClass;
			cout << "请输入联系方式：";
			cin >> StuContact;
		}
		//若有
		else
		{
			
			STUDENT* Info = new STUDENT;	//动态定义结构体指针
			Info = Stu.GetTheStudent(StuID);	//调用函数，该函数会返回学生信息结构体
			StuID = Info->StuID;
			StuName = Info->StuName;
			StuSex = Info->StuSex;
			StuYear = Info->StuYear;
			StuDepartment = Info->StuDepartment;
			StuClass = Info->StuClass;
			StuContact = Info->StuContact;
			delete Info;	//释放


		}
		system("pause");
		system("cls");
		while (true)
		{
			Meu.ShowWelcome(StuID);	//欢迎界面
			//显示学生菜单函数
			Meu.StuMenu();
			//操作选择函数
			Stu.StuOpration(StuID, StuName, StuSex, StuYear, StuDepartment, StuClass, StuContact);
		}

	}
	//选择退出系统
	else if (ISelect == "0")
	{

		cout << "欢迎您下次使用，再见！" << endl;
		system("pause");
	}
	else //输入错误，重新输入
	{
		cout << "输入错误，请输入“1”、“2”或“0”" << endl;
		cout << endl;
		goto loop;
	}
	return 0;
}
