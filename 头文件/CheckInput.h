#pragma once
#include <iostream>
#include <sstream> //加这个头文件,istringstream用到
using namespace std;

long strlong(string InPut);		//string->long
int strint(string str);			//string->int
bool checkint(string InPut);	//判断输入是否为正整数
int check(string Select ,int a,int b);//判断输入的是否为特定范围的数，若是，则返回输入值
