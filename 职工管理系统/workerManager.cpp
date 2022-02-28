#include "workerManager.h"
#include "Worker.h"
#include <iostream>
#include <string>
using namespace std;

WorkerManager::WorkerManager(string employeesFile)
{
	m_employeesFile = employeesFile;	
}
WorkerManager::~WorkerManager()
{
}
void WorkerManager::showMenu()
{
	cout << "*****************************************" << endl;
	cout << "*********欢迎使用职工管理系统！**********" << endl;
	cout << "********* 0.退出管理程序 ****************" << endl;
	cout << "********* 1.增加职工信息 ****************" << endl;
	cout << "********* 2.显示职工信息 ****************" << endl;
	cout << "********* 3.删除离职职工 ****************" << endl;
	cout << "********* 4.修改职工信息 ****************" << endl;
	cout << "********* 5.查找职工信息 ****************" << endl;
	cout << "********* 6.按照编号排序 ****************" << endl;
	cout << "********* 7.清空所有文档 ****************" << endl;
	cout << "*****************************************" << endl;
	cout << endl;
	cout << "请选择你要执行的操作:" << endl;
}
void WorkerManager::exitSystem()
{
	cout << "欢迎下次使用!" << endl;
	system("pause");
	exit(0);
}

bool WorkerManager::idExists(const int id)
{
	FILE * f = fopen(m_employeesFile.c_str(), "r");
	if (f == NULL)
	{
		return false;
	}
	int f_id;
	char name[20];
	int depId;
	while (!feof(f))
	{
		if (fscanf(f, "%d\t%s\t%d", &f_id, name, &depId) != 3)
		{
			break;
		}
		if (f_id == id)
		{
			fclose(f);
			return true;
		}
	}
	fclose(f);
	return false;
}

bool WorkerManager::nameExists(const char * name)
{
	FILE * f = fopen(m_employeesFile.c_str(), "r");
	if (f == NULL)
	{
		return false;
	}
	char fname[20];
	int id, depId;
	while (!feof(f))
	{
		if (fscanf(f, "%d\t%s\t%d\n", &id, fname, &depId) != 3)
		{
			break;
		}
		if (strcmp(name, fname) == 0)
		{
			fclose(f);
			return true;
		}
	}
	fclose(f);
	return false;
}

void WorkerManager::addEmployee()
{
	int id;
	a:cout << "请输入职工编号:" << endl;
	cin >> id;
	//判断id是否重复
	if (idExists(id))
	{
		cout << "id重复，输入无效";
		goto a;
	}
	string name;
	int depId;
	cout << "请输入职工姓名:" << endl;
	cin >> name;
	cout << "请输入部门Id:" << endl;
	cin >> depId;
	FILE * f = fopen(m_employeesFile.c_str(), "a");
	fprintf(f, "%d\t%s\t%d\n", id, name.c_str(), depId);
	fclose(f);
	return;
}
void WorkerManager::batchAddEmployees()
{
	int n;
	cout << "请输入要添加的员工人数:" << endl;
	cin >> n;
	if (n <= 0)
	{
		cout << "输入错误！";
		return;
	}
	for (int i = 0;i < n;i++)
	{
		addEmployee();
	}
	return;
}
void WorkerManager::showEmployees()
{
	FILE * f = fopen(m_employeesFile.c_str(), "r");
	if (f == NULL)
	{
		cout << "员工信息暂无" << endl;
		return;
	}
	cout << "职工编号" << "\t" << "职工姓名" << "\t" << "部门编号" << "\t" << "任务描述" << endl;
	int id;
	char name[20];
	int depId;
	while (!feof(f))
	{
		Worker * worker;
		if (fscanf(f, "%d\t%s\t%d", &id, name, &depId) != 3)
		{
			return;
		}
		if (depId==0)
		{
			worker= new Boss(id, string(name), depId);
		}
		else if (depId == 1)
		{
			worker= new Manager(id, string(name), depId);
		}
		else
		{
			worker =new Employee(id, string(name), depId);
		}
		cout << worker->getId() << "\t" << worker->getName() << "\t" << worker->getDepId() << "\t" << worker->doWork()<<endl;
	}
	cout << "已显示所有员工信息" << endl;
	fclose(f);
	return;
}


void WorkerManager::delEmployee(int id, const char * name)
{
	if (id != -1 )
	{
		if (!idExists(id))
		{
			cout << "该员工不存在！" << endl;
			return;
		}
	}
	else
	{
		if (!nameExists(name))
		{
			cout << "该员工不存在！" << endl;
			return;
		}
	}
	//抽象类不能实例化，但抽象类的指针可以实例化
	Worker **workers = new Worker*[1000];
	int i = 0;
	FILE * f = fopen(m_employeesFile.c_str(), "r");
	int fid, fdepId;
	char fname[20];
	while (!feof(f))
	{
		fscanf(f, "%d\t%s\t%d\n", &fid, fname, &fdepId);
		if (id == fid || strcmp(fname, name)==0)
		{
			continue;
		}
		if (fdepId == 0)
		{
			workers[i] = new Boss(fid, string(fname), fdepId);
		}
		else if (fdepId == 1)
		{
			workers[i] = new Manager(fid, string(fname), fdepId);
		}
		else
		{
			workers[i] = new Employee(fid, string(fname), fdepId);
		}
		i++;
	}
	fclose(f);
	//重新写入文件
	f = fopen(m_employeesFile.c_str(), "w");
	int n = i;
	for (int i = 0;i < n;i++)
	{
		fprintf(f, "%d\t%s\t%d\n", workers[i]->getId(), (workers[i]->getName()).c_str(), workers[i]->getDepId());
	}
	fclose(f);
	delete[] workers;
	return;
}

void WorkerManager::modifyEmployee()
{
	int id;
	cout << "请输入待修改信息的职工编号：" << endl;
	cin >> id;
	bool flag = idExists(id);
	if (!flag)
	{
		cout << "该用户不存在!" << endl;
		return;
	}
	delEmployee(id);
	addEmployee();
	return;
}

void WorkerManager::searchEmployee()
{
	int sType;
	cout << "按职工Id检索，请输入0；按职工姓名检索，请输入1";
	cin >> sType;
	string name="";
	int id=-1;
	if (sType == 0)
	{
		cout << "请输入职工Id：" << endl;
		cin >> id;
	}
	else if(sType==1)
	{
		cout << "请输入职工姓名：" << endl;
		cin >> name;
	}
	else
	{
		cout << "输入错误" << endl;
		return;
	}
	FILE * f = fopen(m_employeesFile.c_str(), "r");
	if (f == NULL)
	{
		cout << "未检索到该员工信息!" << endl;
		return;
	}
	int fid, fdepId;
	char fname[20];
	while (!feof(f))
	{
		fscanf(f, "%d\t%s\t%d\n", &fid, fname, &fdepId);
		if (fid == id || strcmp(fname, name.c_str()) == 0)
		{
			cout << fid << "\t" << fname << "\t" << fdepId << endl;
		}
	}
	return;
}
//关系运算符重载，用于直接比较两个指向worker的指针

void WorkerManager::sortEmployees()
{
	FILE * f = fopen(m_employeesFile.c_str(), "r");
	if (f == NULL)
	{
		cout << "排序完毕!" << endl;
		return;
	}
	Worker * workers[1000];
	int n = 0;
	int id, depId;
	char name[20];
	while (!feof(f))
	{
		if (fscanf(f, "%d\t%s\t%d\n", &id, name, &depId) != 3)
		{
			break;
		}
		if (depId == 1)
		{
			workers[n] = new Boss(id, string(name), depId);
		}
		else if (depId == 2)
		{
			workers[n] = new Manager(id, string(name), depId);
		}
		else
		{
			workers[n] = new Employee(id, string(name), depId);
		}
		n++;
	}
	fclose(f);
	if (n >= 2)
	{
		bool flag;
		for (int i = 0; i < n-1; i++)
		{
			flag = true;
			for (int j = 0;j < n - 1 - i;j++)
			{
				if (*workers[j] > workers[j + 1])
				{
					Worker * tmp = workers[j];
					workers[j] = workers[j + 1];
					workers[j + 1] = tmp;
					flag = false;
				}
			}
			if (flag)
			{
				break;
			}
		}
	}
	//输出排序信息，写入排序信息
	f = fopen(m_employeesFile.c_str(), "w");
	for (int i = 0;i < n;i++)
	{
		fprintf(f, "%d\t%s\t%d\n", workers[i]->getId(), (workers[i]->getName()).c_str(), workers[i]->getDepId());
		cout << workers[i]->getId()<<"\t" <<workers[i]->getName()<<"\t"<< workers[i]->getDepId()<<endl;
	}
	fclose(f);
	cout << "排序完毕!" << endl;
}

void WorkerManager::emptyAll()
{
	FILE * f = fopen(m_employeesFile.c_str(), "w");
	fclose(f);
	cout << "数据已清空完毕!" << endl;
	return;
}


