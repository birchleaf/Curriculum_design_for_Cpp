#include "Student.h"


Student::Student()
{
	ifstream ifs;	//创建输入流
	ifs.open(FILE, ios::in);	//打开文件，读

	//若打不开文件，即未查找到文件
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		this->Count = 0;		//课程数为0
		this->COURSE = NULL;	//Course父类指针为空
		ifs.close();	//关闭文件
		return;		//结束此函数
	}
	//若文件存在，判断文件内是否有数据
	char buf;
	ifs >> buf;
	//无数据
	if (ifs.eof())
	{
		cout << "文件存在，但数据为空" << endl;
		this->Count = 0;
		this->COURSE = NULL;
		ifs.close();
		return;
	}
	//有数据
	else
	{
		this->Count = StuCourseCount();	 //读取课程数量
		//创建一个指针数组，数组长度为课程数量，并让COURSE指向这个指针数组
		this->COURSE = new Course * [this->Count];
		this->StuReadFile();		//读取文件
		ifs.close();			//关闭文件
		cout << "课程数为: " << Count << endl;
		cout << "学生系统数据读取成功！" << endl;
	}

}


void Student::StuReadFile()
{

	ifstream ifs;
	ifs.open(FILE, ios::in);
	long num;               //课程编号 
	string name;			//课程名称   
	string kind;			//课程性质   
	string stime;              //总学时   
	string score;				//学分    
	string term;				//开课学期   
	int PeopleCount;		//已报名人数
	int ReadCourse = 0;		//已读取的课程数量，用这个定位存入的数组中的位置

	//学生信息
	long StuID;				//学号
	string StuName;
	string StuSex;
	string StuYear;
	string StuDepartment;
	string StuClass;
	string StuContact;

	//逐个读取课程数据,读到空格则读下一个变量
	while (ifs >> num && ifs >> name && ifs >> kind && ifs >> stime && ifs >> score
		&& ifs >> term && ifs >> PeopleCount)
	{
		Course* Cour = NULL;	//创建一个指针对象Cour
		//若所读取的课程性质为必修课
		if (kind == "必修课")
		{

			/*new一个必修课对象，并调用构造函数进行初始化，将读取的数据赋值为构造函数的参数值
			* 让Cour指针接收这个对象
			*/
			Cour = new Compulsory(num, name, stime, score, term, PeopleCount);
			//读取学号信息

			int ReadPeople = 0;	//已读取的学生个数，用法同上
			if (ReadPeople == Cour->PeopleCount)
			{
				goto loop;
			}
			while (ifs >> StuID && ifs >> StuName && ifs >> StuSex && ifs >> StuYear && ifs >> StuDepartment && ifs >> StuClass
				&& ifs >> StuContact)
			{
				
				Cour->Student[ReadPeople].StuID = StuID;	//录入学号
				Cour->Student[ReadPeople].StuName = StuName;
				Cour->Student[ReadPeople].StuSex = StuSex;
				Cour->Student[ReadPeople].StuYear = StuYear;
				Cour->Student[ReadPeople].StuDepartment = StuDepartment;
				Cour->Student[ReadPeople].StuClass = StuClass;
				Cour->Student[ReadPeople].StuContact = StuContact;
				ReadPeople++;
				if (ReadPeople == Cour->PeopleCount)
				{
					break;
				}



			}
		}
		//若所读取的课程性质为选修课
		else
		{
			Cour = new Optional(num, name, stime, score, term, PeopleCount);

			int ReadPeople = 0;
			if (ReadPeople == Cour->PeopleCount)
			{
				goto loop;
			}
			while (ifs >> StuID && ifs >> StuName && ifs >> StuSex && ifs >> StuYear && ifs >> StuDepartment && ifs >> StuClass
				&& ifs >> StuContact)
			{
				
				
				Cour->Student[ReadPeople].StuID = StuID;	//录入学号
				Cour->Student[ReadPeople].StuName = StuName;
				Cour->Student[ReadPeople].StuSex = StuSex;
				Cour->Student[ReadPeople].StuYear = StuYear;
				Cour->Student[ReadPeople].StuDepartment = StuDepartment;
				Cour->Student[ReadPeople].StuClass = StuClass;
				Cour->Student[ReadPeople].StuContact = StuContact;
				ReadPeople++;
				if (ReadPeople == Cour->PeopleCount)
				{
					break;
				}
			}


		}

		loop:this->COURSE[ReadCourse] = Cour;

		ReadCourse++;
	}
	ifs.close();
}



int Student::StuCourseCount()
{
	ifstream ifs;
	ifs.open(FILE, ios::in);
	int Count = 0;	//记录课程数量
	string buf;
	while (getline(ifs, buf))	//逐行读取，每读取一行，count+1
	{
		Count++;
	}
	return Count;	//返回课程数量
}



void Student::StuPrintCourse()
{


	for (int i = 0; i < this->Count; i++)
	{
		this->COURSE[i]->PrintCourse();
		cout << "-------------------------------------------------------------------------" << endl;
	}


}



void Student::HaveCourse(long StuID)	//传入学号
{
	for (int i = 0; i < this->Count; i++)

	{
		for (int j = 0; j < this->COURSE[i]->PeopleCount; j++)
		{
			if (this->COURSE[i]->Student[j].StuID == StuID)
			{
				this->COURSE[i]->PrintCourse();
				cout << "-------------------------------------------------------------------------" << endl;
			}
		}

	}
}


void Student::StuAdd(int num, long StuID, string StuName, string StuSex, string StuYear, string StuDepartment, string StuClass, string StuContact)	//传入编号、学号
{
	int x = -1;
	for (int i = 0; i < this->Count; i++)
	{
		if (this->COURSE[i]->num == num)
		{
			x = i;
			this->COURSE[x]->PrintCourse();
			cout << "-------------------------------------------------------------------------" << endl;
			for (int j = 0; j < this->COURSE[i]->PeopleCount; j++)
			{
				if (this->COURSE[i]->Student[j].StuID == StuID)
				{
					cout << "您已选该课" << endl;
					return;
				}
			}
		}
	}
	if (x == -1)
	{
		cout << "课程编号不存在" << endl;
		
	}
	else
	{
		//KECH数组中编号为num的课程中的StuID数组内添加一位学生，
		this->COURSE[x]->Student[this->COURSE[x]->PeopleCount].StuID = StuID;
		this->COURSE[x]->Student[this->COURSE[x]->PeopleCount].StuName = StuName;
		this->COURSE[x]->Student[this->COURSE[x]->PeopleCount].StuSex = StuSex;
		this->COURSE[x]->Student[this->COURSE[x]->PeopleCount].StuYear = StuYear;
		this->COURSE[x]->Student[this->COURSE[x]->PeopleCount].StuDepartment = StuDepartment;
		this->COURSE[x]->Student[this->COURSE[x]->PeopleCount].StuClass = StuClass;
		this->COURSE[x]->Student[this->COURSE[x]->PeopleCount].StuContact = StuContact;
		this->COURSE[x]->PeopleCount++;
		cout << "选课成功" << endl;
	}

	
}


bool Student::CheckStudent(long StuID)
{
	
	for (int i = 0; i < this->Count; i++)
	{
		for (int j = 0; j < COURSE[i]->PeopleCount; j++)
		{
			if (this->COURSE[i]->Student[j].StuID == StuID)
			{
				StuID = this->COURSE[i]->Student[j].StuID;
				
				return true;
			}
				
		}
		
	}
	return false;
}


struct STUDENT* Student::GetTheStudent(long StuID)
{
	STUDENT* Info =new STUDENT;
	for (int i = 0; i < this->Count; i++)
	{
		for (int j = 0; j < COURSE[i]->PeopleCount; j++)
		{
			if (this->COURSE[i]->Student[j].StuID == StuID)
			{
				Info->StuID = this->COURSE[i]->Student[j].StuID;
				Info->StuName = this->COURSE[i]->Student[j].StuName;
				Info->StuSex = this->COURSE[i]->Student[j].StuSex;
				Info->StuYear = this->COURSE[i]->Student[j].StuYear;
				Info->StuDepartment = this->COURSE[i]->Student[j].StuDepartment;
				Info->StuClass = this->COURSE[i]->Student[j].StuClass;
				Info->StuContact = this->COURSE[i]->Student[j].StuContact;
				return Info;
			}
		}
	}


}





//查询课程信息并返回该课程在数组中的定位
long Student::StuSearch(int num)	//传入编号
{
	for (int i = 0; i < this->Count; i++)
	{
		if (this->COURSE[i]->num == num)
		{
			this->COURSE[i]->PrintCourse();
			cout << "-------------------------------------------------------------------------" << endl;
			return i;
		}
	}
	return -1;
}



void Student::Studel(int num, long StuID)	//传入编号、学号
{

	int x = -1;
	for (int i = 0; i < this->Count; i++)
	{
		if (this->COURSE[i]->num == num)
		{
			x = i;
			break;
		}

	}
	if (x == -1)
	{
		cout << "课程编号不存在" << endl;
		return;
	}
	for (int j = 0; j < this->COURSE[x]->PeopleCount; j++)
	{
		this->COURSE[x]->PrintCourse();
		cout << "-------------------------------------------------------------------------" << endl;
		if (this->COURSE[x]->Student[j].StuID == StuID)
		{
			for (int k = j; k < MAX - 1; k++)
			{
				this->COURSE[x]->Student[k] = this->COURSE[x]->Student[k + 1];
			}
			this->COURSE[x]->PeopleCount--;
			cout << "退课成功" << endl;
			return;
		}
	}

}

void Student::StuSaveFile()
{
	ofstream ofs;
	ofs.open(FILE, ios::out);
	for (int i = 0; i < this->Count; i++)
	{
		//读取课程信息
		ofs << this->COURSE[i]->num << " "
			<< this->COURSE[i]->name << " "
			<< this->COURSE[i]->kind << " "
			<< this->COURSE[i]->stime << " "
			<< this->COURSE[i]->score << " "
			<< this->COURSE[i]->term << " "
			<< this->COURSE[i]->PeopleCount << " ";
		//读取学生信息
		for (int j = 0; j < this->COURSE[i]->PeopleCount; j++)
		{
			ofs << this->COURSE[i]->Student[j].StuID << " ";
			ofs << this->COURSE[i]->Student[j].StuName << " ";
			ofs << this->COURSE[i]->Student[j].StuSex << " ";
			ofs << this->COURSE[i]->Student[j].StuYear << " ";
			ofs << this->COURSE[i]->Student[j].StuDepartment << " ";
			ofs << this->COURSE[i]->Student[j].StuClass << " ";
			ofs << this->COURSE[i]->Student[j].StuContact << " ";
		}
		ofs << endl;
	}
	ofs.close();
}


//操作
void Student::StuOpration(long StuID, string StuName, string StuSex, string StuYear, string StuDepartment, string StuClass, string StuContact)
{

	int x = -1;


loop:	cin >> x;
	switch (x)
	{
	case 1:	//浏览
		system("cls");
		cout << "***您选择了：1.浏览所有课程信息***" << endl << endl;
		this->StuPrintCourse();
		system("pause");
		system("cls");
		break;
	case 2:	//查询
	{
		system("cls");
		cout << "***您选择了：2.查询指定课程信息***" << endl << endl;
		cout << "请输入所查询课程的编号: ";
		cin >> x;
		this->StuSearch(x);
		system("pause");
		system("cls");
	}
	break;
	case 3://查看已选
		system("cls");
		cout << "***您选择了：3.查看已选***" << endl << endl;
		this->HaveCourse(StuID);
		system("pause");
		system("cls");

		break;
	case 4:	//选课
	{
		system("cls");
		cout << "***您选择了：4.选课***" << endl << endl;
		cout << "请输入课程编号: ";
		cin >> x;
		this->StuAdd(x, StuID, StuName, StuSex, StuYear, StuDepartment, StuClass, StuContact);
		this->StuSaveFile();
		system("pause");
		system("cls");
	}
	break;
	case 5:	//退课
	{
		system("cls");
		cout << "***您选择了：5.退课***" << endl << endl;
		cout << "请输入课程编号: ";
		cin >> x;
		this->Studel(x, StuID);

		this->StuSaveFile();
		system("pause");
		system("cls");
	}
	break;
	case 6:	//保存
		system("cls");
		cout << "***您选择了：6.手动保存***" << endl << endl;
		this->StuSaveFile();
		system("pause");
		system("cls");
		break;
	case 0:
		if (!CheckStudent(StuID))
		{
			cout << "您还未选课，若退出系统，您的数据将清空，确认退出吗？" << endl;
			cout << "1->确认" << endl;
			cout << "2->取消" << endl;
			cin >> x;
		}
		if (x == 2)
		{
			cout << "已取消" << endl;
			goto loop;
		}
		cout << "欢迎您下次使用，再见！" << endl;
		this->StuSaveFile();
		system("pause");
		exit(0);
	default:
		cout << "请输入正确的数字来选择选项" << endl;
		goto loop;
		break;

	}


}


Student::~Student()
{
	this->Count = 0;
	delete[] this->COURSE;
}



