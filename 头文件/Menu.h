#pragma once
#include <iostream>
using namespace std;
class Menu
{
public:
	void IndentityMenu();		//身份验证界面
	void AdmMenu();				//管理员选择界面
	void StuMenu();				//学生界面
	
	/*声明并定义一个输出欢迎文字函数模板，若为管理员，输出“欢迎你，管理员”（string型）；否则
	*输出“欢迎你”，并输出学生学号（long型)
	*/
	template<typename T>
	void ShowWelcome(T Welcome)
	{
		cout << endl;
		cout << "欢迎你，"<<Welcome<<endl;
	}
};
	


