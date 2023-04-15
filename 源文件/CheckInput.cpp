#include "CheckInput.h"


// string 转 int
int strint(string str)
{
	
	return atoi(str.c_str()); //atoi:char-->int;c_str:string-->char;
}

//string转long，用来返回学生学号
long strlong(string InPut)
{
	long x;
	istringstream is(InPut); 
	is >> x;
	return x;
}


//判断输入的字符串是否为正整数,若为正整数，返回真，否则返回假
bool checkint(string InPut)
{
	char* a = new char[InPut.length()];
	strcpy(a, InPut.c_str());
	
	for (int i = 0; i < InPut.length(); i++)
	{
		//如果不是数字
		if (!isdigit(a[i]))
		{
			return false;
		}
	}
	//这里不能释放数组a的内存空间，会崩溃，不知道为什么？？？
	return true;
}



//判断输入的是否为特定范围的数，若是，则返回输入值int
int check(string Select,int a,int b )
{
	int x = strint(Select);

	while (true)
	{
		if (checkint(Select) && x >= a && x <= b)
		{
			return x;
		}
		else
		{
			cout << "请输入正确的数字" << endl;
			cin >> Select;
			x = strint(Select);
		}

	}
	return -1;
}


