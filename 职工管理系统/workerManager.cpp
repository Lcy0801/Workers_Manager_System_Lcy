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
	cout << "*********��ӭʹ��ְ������ϵͳ��**********" << endl;
	cout << "********* 0.�˳�������� ****************" << endl;
	cout << "********* 1.����ְ����Ϣ ****************" << endl;
	cout << "********* 2.��ʾְ����Ϣ ****************" << endl;
	cout << "********* 3.ɾ����ְְ�� ****************" << endl;
	cout << "********* 4.�޸�ְ����Ϣ ****************" << endl;
	cout << "********* 5.����ְ����Ϣ ****************" << endl;
	cout << "********* 6.���ձ������ ****************" << endl;
	cout << "********* 7.��������ĵ� ****************" << endl;
	cout << "*****************************************" << endl;
	cout << endl;
	cout << "��ѡ����Ҫִ�еĲ���:" << endl;
}
void WorkerManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��!" << endl;
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
	a:cout << "������ְ�����:" << endl;
	cin >> id;
	//�ж�id�Ƿ��ظ�
	if (idExists(id))
	{
		cout << "id�ظ���������Ч";
		goto a;
	}
	string name;
	int depId;
	cout << "������ְ������:" << endl;
	cin >> name;
	cout << "�����벿��Id:" << endl;
	cin >> depId;
	FILE * f = fopen(m_employeesFile.c_str(), "a");
	fprintf(f, "%d\t%s\t%d\n", id, name.c_str(), depId);
	fclose(f);
	return;
}
void WorkerManager::batchAddEmployees()
{
	int n;
	cout << "������Ҫ��ӵ�Ա������:" << endl;
	cin >> n;
	if (n <= 0)
	{
		cout << "�������";
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
		cout << "Ա����Ϣ����" << endl;
		return;
	}
	cout << "ְ�����" << "\t" << "ְ������" << "\t" << "���ű��" << "\t" << "��������" << endl;
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
	cout << "����ʾ����Ա����Ϣ" << endl;
	fclose(f);
	return;
}


void WorkerManager::delEmployee(int id, const char * name)
{
	if (id != -1 )
	{
		if (!idExists(id))
		{
			cout << "��Ա�������ڣ�" << endl;
			return;
		}
	}
	else
	{
		if (!nameExists(name))
		{
			cout << "��Ա�������ڣ�" << endl;
			return;
		}
	}
	//�����಻��ʵ���������������ָ�����ʵ����
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
	//����д���ļ�
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
	cout << "��������޸���Ϣ��ְ����ţ�" << endl;
	cin >> id;
	bool flag = idExists(id);
	if (!flag)
	{
		cout << "���û�������!" << endl;
		return;
	}
	delEmployee(id);
	addEmployee();
	return;
}

void WorkerManager::searchEmployee()
{
	int sType;
	cout << "��ְ��Id������������0����ְ������������������1";
	cin >> sType;
	string name="";
	int id=-1;
	if (sType == 0)
	{
		cout << "������ְ��Id��" << endl;
		cin >> id;
	}
	else if(sType==1)
	{
		cout << "������ְ��������" << endl;
		cin >> name;
	}
	else
	{
		cout << "�������" << endl;
		return;
	}
	FILE * f = fopen(m_employeesFile.c_str(), "r");
	if (f == NULL)
	{
		cout << "δ��������Ա����Ϣ!" << endl;
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
//��ϵ��������أ�����ֱ�ӱȽ�����ָ��worker��ָ��

void WorkerManager::sortEmployees()
{
	FILE * f = fopen(m_employeesFile.c_str(), "r");
	if (f == NULL)
	{
		cout << "�������!" << endl;
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
	//���������Ϣ��д��������Ϣ
	f = fopen(m_employeesFile.c_str(), "w");
	for (int i = 0;i < n;i++)
	{
		fprintf(f, "%d\t%s\t%d\n", workers[i]->getId(), (workers[i]->getName()).c_str(), workers[i]->getDepId());
		cout << workers[i]->getId()<<"\t" <<workers[i]->getName()<<"\t"<< workers[i]->getDepId()<<endl;
	}
	fclose(f);
	cout << "�������!" << endl;
}

void WorkerManager::emptyAll()
{
	FILE * f = fopen(m_employeesFile.c_str(), "w");
	fclose(f);
	cout << "������������!" << endl;
	return;
}


