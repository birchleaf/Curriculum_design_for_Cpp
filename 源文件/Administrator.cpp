#include "Administrator.h"

//构造函数，初始化，即读取文件数据
Administrator::Administrator()
{
	ifstream ifs;	//创建输入流
	ifs.open(FILE, ios::in);	//打开文件，读

	//若打不开文件，即未查找到文件
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		this->Count = 0;		//课程数为0
		this->PeoCou = 0;
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
		this->PeoCou = 0;
		this->COURSE = NULL;
		ifs.close();
		return;
	}
	//有数据
	else
	{
		this->Count = CourseCount();	 //读取课程数量
		//创建一个指针数组，数组长度为课程数量，并让COURSE指向这个指针数组
		this->COURSE = new Course * [this->Count];
		this->ReadFile();		//读取文件
		PeoCou = ReadStuList(); //读取学生
		ifs.close();			//关闭文件
		cout << "课程数为: " << Count << endl;
		cout << "管理员系统数据读取成功！" << endl;
	}

}

//读取并返回文件内课程数量
int Administrator::CourseCount()
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


//读取文件
void Administrator::ReadFile()
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
			
			int ReadPeople = 0;	//已读取的学生个数，用法同上
			//若课程内无学生，则不读取学生
			if (ReadPeople == Cour->PeopleCount)
			{
				goto loop;
			}
			//读取学生信息
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
				//若已读取完学生，停止读取
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

//添加课程，定义一个长度为长度为课程数量+1的指针数组，将添加的课程用此数组接收
void Administrator::Add()
{
	//定义一个指针数组NewCour，长度为课程数量+1
	Course** NewCour = new Course * [this->Count + 1];
	string name;          //课程名称   
	string stime;            //总学时   
	string score;            //学分    
	string term;             //开课学期   
	string kind;
	Course* Cour = NULL;
	//如果课程数量不为0，将原课程数据录入到NewCour中
	if (Count != 0)
	{
		for (int i = 0; i < this->Count; i++)
		{
			NewCour[i] = COURSE[i];
		}
	}
	cout << "请输入所添加课程的名称: ";
	cin >> name;
	cout << "请输入所添加课程的性质 " << endl;;
	cout << "a->必修课" << endl;
	cout << "b->选修课" << endl;
	cin >> kind;
	cout << "请输入所添加课程的总学时: ";
	cin >> stime;
	cout << "请输入所添加课程的学分: ";
	cin >> score;
	cout << "请输入所添加课程的开课学期: ";
	cin >> term;
	if (kind == "a")
	{
		if (Count == 0)
		{
			Cour = new Compulsory(1, name, stime, score, term);
		}
		else
		{
			Cour = new Compulsory(this->COURSE[this->Count - 1]->num + 1, name, stime, score, term);
		}

	}
	else
	{
		if (Count == 0)		//当Count==0时
		{
			Cour = new Optional(1, name, stime, score, term);
		}

		/*若无上文的判断，Count == 0时，会读入arr【 - 1】，访问冲突*/

		else
		{	//读取新添加数组的上一个课程的代码，再+1，避免删除某课程后再添加课程导致的访问冲突
			Cour = new Optional(this->COURSE[this->Count - 1]->num + 1, name, stime, score, term);
		}

	}
	NewCour[this->Count] = Cour;	//数组末尾接收Cour
	delete[] this->COURSE;			//释放动态空间
	this->COURSE = NewCour;			//指向新数组
	this->Count++;		//课程数+1
	cout << "添加成功" << endl;


}


//输出课程信息和学号
void Administrator::PrintAll()
{

	for (int i = 0; i < this->Count; i++)
	{
		this->COURSE[i]->PrintCourse();
		this->COURSE[i]->PrintStudent();
		
	}

}



//const修饰防止误修改信息
void Administrator::ShowStudent(const list <STUDENT>& StuList)
{
	
	
	list<STUDENT>::iterator Print;
	if (this->PeoCou == 0)
	{
		//delete[] Stu;
		cout << "记录为空！" << endl;
		return;
	}
	else
	{
		cout << "所有学生基本信息: " << endl;
		for (list<STUDENT>::const_iterator Print = StuList.begin(); Print != StuList.end(); Print++)
		{
			cout << "-------------------------------------------------------------------------" << endl;
			cout << "学号" << '\t';
			cout << "姓名" << '\t';
			cout << "性别" << '\t';
			cout << "年龄" << '\t';
			cout << "学分" << '\t';
			cout << "系别" << '\t';
			cout << "联系方式" << endl;
			cout << (*Print).StuID << '\t';
			cout << (*Print).StuName << '\t';
			cout << (*Print).StuSex << '\t';
			cout << (*Print).StuYear << '\t';
			cout << (*Print).StuDepartment << '\t';
			cout << (*Print).StuClass << '\t';
			cout << (*Print).StuContact << endl;
			cout << "-------------------------------------------------------------------------" << endl;
			cout << endl;
		}
	}




}


int Administrator::ReadStuList()
{

	
	StuList.clear();
	list<STUDENT>::iterator Read;
	int PeoCou = 0;
	int x = 0;
	//课程遍历
	for (int i = 0; i < this->Count; i++)
	{
		//遍历课程i内学生信息
		for (int j = 0; j < this->COURSE[i]->PeopleCount; j++)
		{
			x = 0;
			//遍历Stu内已储存的学生信息
			for (list<STUDENT>::const_iterator Read = StuList.begin(); Read != StuList.end(); Read++)
			{
				//比对
				
				if ((*Read).StuID == this->COURSE[i]->Student[j].StuID)
				{
					x = -1;
					break;
				}


			}
			if (x == 0)
			{
			
				StuList.push_back(this->COURSE[i]->Student[j]);

				PeoCou++;
			}

		}

	}
	return PeoCou;
}







void Administrator::Search(long StuID, const list <STUDENT>& StuList)
{

	list<STUDENT>::iterator PrintOne;

	for (list<STUDENT>::const_iterator PrintOne = StuList.begin(); PrintOne != StuList.end(); PrintOne++)
	{
		if ((*PrintOne).StuID == StuID)
		{
			cout << "-------------------------------------------------------------------------" << endl;
			cout << "该学生基本信息: " << endl;
			cout << "学号" << '\t';
			cout << "姓名" << '\t';
			cout << "性别" << '\t';
			cout << "年龄" << '\t';
			cout << "系别" << '\t';
			cout << "班级" << '\t';
			cout << "联系方式" << endl;
			cout << (*PrintOne).StuID << '\t';
			cout << (*PrintOne).StuName << '\t';
			cout << (*PrintOne).StuSex << '\t';
			cout << (*PrintOne).StuYear << '\t';
			cout << (*PrintOne).StuDepartment << '\t';
			cout << (*PrintOne).StuClass << '\t';
			cout << (*PrintOne).StuContact << endl;
			cout << endl;
			cout << "该学生已选择的课程为：";
			for (int i = 0; i < this->Count; i++)
			{
				for (int j = 0; j < this->COURSE[i]->PeopleCount; j++)
				{
					if (this->COURSE[i]->Student[j].StuID == StuID)
					{
						cout<<this->COURSE[i]->name<<" ";
					}
				}
			}
			cout << endl;
			cout << "-------------------------------------------------------------------------" << endl;
			return;
		}
	}
	cout << "该学生不存在 " << endl;
}


//查询课程信息并返回该课程在数组中的定位
long Administrator::Search(int num)	//传入编号
{

	for (int i = 0; i < this->Count; i++)
	{
		if (this->COURSE[i]->num == num)
		{
			this->COURSE[i]->PrintCourse();
			this->COURSE[i]->PrintStudent();
			return i;
		}
	}
	cout << "记录为空!" << endl;
	return -1;
}

//添加学生
void Administrator::Add(int num, long StuID)//传入编号、学号
{
	string StuName;
	string StuSex;
	string StuYear;
	string StuDepartment;
	string StuClass;
	string StuContact;
	int x = -1;
	//遍历所有课程
	for (int i = 0; i < this->Count; i++)
	{
		//若存在此编号的课程
		if (this->COURSE[i]->num == num)
		{
			x = i;	//记录课程在数组中的位置
			//遍历该课程内学生学号
			for (int j = 0; j < this->COURSE[i]->PeopleCount; j++)
			{
				//若已存在该学号
				if (this->COURSE[i]->Student[j].StuID == StuID)
				{
					cout << "该学生已存在" << endl;
					return;
				}
			}
		}

	}
	//若不存在此编号的课程
	if (x == -1)
	{
		cout << "课程编号不存在" << endl;
		return;
	}
	//存在
	else
	{
		//遍历所有课程信息
		for (int i = 0; i < this->Count; i++)
		{
			//遍历所有学生信息，查找其他课程是否已有该学生
			for (int j = 0; j < this->COURSE[i]->PeopleCount; j++)
			{
				//查找到该学生
				if (this->COURSE[i]->Student[j].StuID == StuID)
				{
					StuName = this->COURSE[i]->Student[j].StuName;
					StuSex = this->COURSE[i]->Student[j].StuSex;
					StuYear = this->COURSE[i]->Student[j].StuYear;
					StuDepartment = this->COURSE[i]->Student[j].StuDepartment;
					StuClass = this->COURSE[i]->Student[j].StuClass;
					StuContact = this->COURSE[i]->Student[j].StuContact;
					this->COURSE[x]->Student[this->COURSE[x]->PeopleCount].StuID = StuID;
					this->COURSE[x]->Student[this->COURSE[x]->PeopleCount].StuName = StuName;
					this->COURSE[x]->Student[this->COURSE[x]->PeopleCount].StuSex = StuSex;
					this->COURSE[x]->Student[this->COURSE[x]->PeopleCount].StuYear = StuYear;
					this->COURSE[x]->Student[this->COURSE[x]->PeopleCount].StuDepartment = StuDepartment;
					this->COURSE[x]->Student[this->COURSE[x]->PeopleCount].StuClass = StuClass;
					this->COURSE[x]->Student[this->COURSE[x]->PeopleCount].StuContact = StuContact;
					this->COURSE[x]->PeopleCount++;
					cout << "添加学生成功" << endl;
					return;
				}
			}

		}


		//COURSE数组中位置为x的对象中的学生结构体数组内添加一位学生，
		this->COURSE[x]->Student[this->COURSE[x]->PeopleCount].StuID = StuID;
		cout << "学号已录入，请继续填写学生的其他信息" << endl;
		cout << "姓名：";
		cin >> StuName;
		cout << "姓别：";
		cin >> StuSex;
		cout << "年龄：";
		cin >> StuYear;
		cout << "系别：";
		cin >> StuDepartment;
		cout << "班级：";
		cin >> StuClass;
		cout << "联系方式：";
		cin >> StuContact;
		this->COURSE[x]->Student[this->COURSE[x]->PeopleCount].StuName = StuName;
		this->COURSE[x]->Student[this->COURSE[x]->PeopleCount].StuSex = StuSex;
		this->COURSE[x]->Student[this->COURSE[x]->PeopleCount].StuYear = StuYear;
		this->COURSE[x]->Student[this->COURSE[x]->PeopleCount].StuDepartment = StuDepartment;
		this->COURSE[x]->Student[this->COURSE[x]->PeopleCount].StuClass = StuClass;
		this->COURSE[x]->Student[this->COURSE[x]->PeopleCount].StuContact = StuContact;


		this->COURSE[x]->PeopleCount++;
		cout << "添加学生成功" << endl;
	}

};

//删除课程
void Administrator::del(int x)	//传入数组位置
{
	//选择Count-2而非Count-1，是为了避免数组越界
	//若删除的课程在数组的最后一位，则无需覆盖，直接让课程数（Count）自减，使读取不到该课程信息即可
	for (int i = x; i < this->Count - 2; i++)	
	{
		COURSE[i] = COURSE[i + 1];
	}
	this->Count--;
	cout << "删除课程成功" << endl;
}

//删除学生
void Administrator::del(int num, long StuID)//传入编号、学号
{

	int x = -1;

	for (int i = 0; i < this->Count; i++)
	{
		//课程编号存在
		if (this->COURSE[i]->num == num)
		{
			x = i;	//记录在数组中的位置
			break;
		}

	}

	if (x == -1)
	{
		cout << "该课程不存在" << endl;
		return ;
	}
	for (int j = 0; j < this->COURSE[x]->PeopleCount; j++)
	{
		//查找到该学号
		if (this->COURSE[x]->Student[j].StuID == StuID)
		{
			//覆盖删除
			for (int k = j; k < MAX - 2; k++)
			{
				this->COURSE[x]->Student[k] = this->COURSE[x]->Student[k + 1];
			}
			this->COURSE[x]->PeopleCount--;
			cout << "删除成功" << endl;
			return ;
		}
	}
	//课程编号存在。但查不到该学号
	//返回数组位置
	cout << "记录为空！" << endl;
	return ;
}


//修改课程信息（课程编号不可改!!!）
void Administrator::Change(int x)	//传入数组位置
{


	if (x == -1)
	{
		cout << "课程编号不存在" << endl;
		return;
	}
	cout << "请输入所修改课程的名称: ";
	cin >> this->COURSE[x]->name;
	cout << "请输入所添加课程的性质 " << endl;;
	cout << "a->必修课" << endl;
	cout << "其他->选修课" << endl;
	string kind;
	cin >> kind;
	if (kind == "a")
	{
		this->COURSE[x]->kind = "必修课";
	}
	else
	{
		this->COURSE[x]->kind = "选修课";
	}
	cout << "请输入所修改课程的总学时: ";
	cin >> this->COURSE[x]->stime;
	cout << "请输入所修改课程的学分: ";
	cin >> this->COURSE[x]->score;
	cout << "请输入所修改课程的开课学期: ";
	cin >> this->COURSE[x]->term;
	cout << "修改成功！" << endl;
}

//保存数据
void Administrator::SaveFile()
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
		ofs << endl;	//储存完一门课程信息（包括学生信息）后，换行
						//一门课程信息（包括学生信息）占一行
	}
	ofs.close();
}


//学号不可改！！！
void Administrator::Change(long StuID)	//传入学号
{
	string StuName;
	string StuSex;
	string StuYear;
	string StuDepartment;
	string StuClass;
	string StuContact;
	int x = -1;
	cout << "姓名：";
	cin >> StuName;
	cout << "姓别：";
	cin >> StuSex;
	cout << "年龄：";
	cin >> StuYear;
	cout << "系别：";
	cin >> StuDepartment;
	cout << "班级：";
	cin >> StuClass;
	cout << "联系方式：";
	cin >> StuContact;

	for (int i = 0; i < this->Count; i++)
	{
		for (int j = 0; j < this->COURSE[i]->PeopleCount; j++)
		{
			if (this->COURSE[i]->Student[j].StuID == StuID)
			{
				x = 1;

				this->COURSE[i]->Student[j].StuName = StuName;
				this->COURSE[i]->Student[j].StuSex = StuSex;
				this->COURSE[i]->Student[j].StuYear = StuYear;
				this->COURSE[i]->Student[j].StuDepartment = StuDepartment;
				this->COURSE[i]->Student[j].StuClass = StuClass;
				this->COURSE[i]->Student[j].StuContact = StuContact;
			}
		}


	}
	cout << "修改学生信息成功" << endl;
	return;

	if (x == -1)
	{
		cout << "学生不存在" << endl;
		return;
	}


}

void Administrator::Opration()
{
	long x = -1;
loop:  cin >> x;
	switch (x)
	{
	case 1:		//输出所有数据
		system("cls");
		cout << "***您选择了：1.浏览所有信息***" << endl << endl;
		cout << "浏览所有课程信息还是学生信息？" << endl;
		cout << "1->课程" << endl;
		cout << "2->学生" << endl;
		cin >> x;
		if (x == 1)
		{
			this->PrintAll();
		}
		else
		{
			this->ShowStudent(StuList);
		}
		system("pause");
		system("cls");


		break;
	case 2:		//查询某课程
	{
		system("cls");
		cout << "***您选择了：2.查询指定信息***" << endl << endl;
		cout << "查询指定课程信息还是学生信息？" << endl;
		cout << "1->课程" << endl;
		cout << "2->学生" << endl;
		cin >> x;
		if (x == 1)
		{
			cout << "请输入所查询课程的编号: ";
			int num;
			cin >> num;
			this->Search(num);

		}
		else
		{
			cout << "请输入所查询学生的学号: ";
			cin >> x;
			this->Search(x, StuList);
			//this->ReadSStu();
		}
		system("pause");
		system("cls");
	}

	break;
	case 3:		//添加课程
		system("cls");
		cout << "***您选择了：3.添加课程***" << endl << endl;
		this->Add();
		this->SaveFile();
		system("pause");
		system("cls");
		break;
	case 4:
		system("cls");
		cout << "***您选择了：4.向课程内添加学生***" << endl << endl;

		long StuID;
		cout << "请输入课程编号: ";
		cin >> x;
		cout << "请输入学生学号: ";

		cin >> StuID;
		this->Add(x, StuID);
		this->SaveFile();
		this->PeoCou = ReadStuList();
		system("pause");
		system("cls");


		break;
	case 5:		//修改课程或学生
		system("cls");
		cout << "***您选择了：5.修改课程或学生信息***" << endl << endl;
		cout << "修改课程还是学生？" << endl;
		cout << "1->课程" << endl;
		cout << "2->学生" << endl;
		cin >> x;
		if (x == 1)
		{
			cout << "请输入课程编号: ";
			int num;
			cin >> num;
			num = this->Search(num);
			this->Change(num);

		}
		else
		{
			long StuID;
			cout << "请输入学生学号: ";
			cin >> StuID;
			this->Change(StuID);
		}
		this->SaveFile();
		this->PeoCou = ReadStuList();
		system("pause");
		system("cls");
		break;
	case 6:
		system("cls");
		cout << "***您选择了：6.删除课程或学生信息***" << endl << endl;
		cout << "删除课程还是学生？" << endl;
		cout << "1->课程" << endl;
		cout << "2->学生" << endl;
		cin >> x;
		if (x == 1)
		{
			cout << "请输入课程编号: ";
			int num;
			cin >> num;
			int Location;
			Location = this->Search(num);	//获取数组位置
			this->del(Location);

		}
		else
		{
			int num;
			long StuID;
			cout << "请输入课程编号: ";
			cin >> num;

			cout << "请输入学生学号: ";
			cin >> StuID;
			this->del(num, StuID);

		}
		this->SaveFile();
		this->PeoCou=ReadStuList();
		system("pause");
		system("cls");
		break;
	case 7:
		system("cls");
		cout << "***您选择了：7.统计相关信息" << endl;
		cout << "请选择统计的信息？" << endl;
		cout << "1->课程的门数" << endl;
		cout << "2->学生总人数" << endl;
		cout << "3->选择某门课程的学生人数" << endl;

		cin >> x;
		if (x == 1)
		{
			cout << "课程的门数为：" << this->Count << "门" << endl;
		}
		else if (x == 2)
		{
			cout << "学生总人数为：" << this->PeoCou << "人" << endl;
		}

		else
		{
			int num;
			cout << "请输入课程编号: ";
			cin >> num;
			cout << endl;
			cout << "选修该课程的学生人数为：" <<this->COURSE[this->Search(num)]->PeopleCount<<"人"<< endl;
			

		}
		system("pause");
		system("cls");
		break;
	case 8:
		system("cls");
		cout << "***您选择了：8.手动保存***" << endl << endl;
		this->SaveFile();
		system("pause");
		system("cls");
		break;
	case 9:
		system("cls");
		cout << "***您选择了：9.格式化(需手动保存)***" << endl << endl;
		this->Count = 0;	//课程数赋值为0，使得读取不到课程数组
		StuList.clear();
		cout << "格式化成功，请手动保存" << endl;
		system("pause");
		system("cls");
		break;
	case 0:
		cout << "欢迎您下次使用，再见！" << endl;
		this->SaveFile();
		system("pause");
		exit(0);
		break;
	default:
		cout << "请输入正确的数字来选择选项" << endl;
		goto loop;
		break;
	}
};


Administrator::~Administrator()
{
	this->Count = 0;
	this->PeoCou = 0;
	delete[] this->COURSE;
}