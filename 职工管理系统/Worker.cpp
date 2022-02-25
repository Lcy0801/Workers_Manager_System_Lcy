#include "Worker.h"
#include <iostream>
#include <string>
using namespace std;

Worker::Worker(int id, string name,int depId)
{
	m_Id = id;
	m_Name = name;
	m_DepId = depId;
}
Worker::~Worker() {};
void Worker::showName()
{
	cout << m_Name;
}

void Worker::showId() 
{
	cout << m_Id;
}

void Worker::showDepId()
{
	cout << m_DepId;
}


Employee::Employee(int id, string name, int depId) :Worker(id, name, depId) {};
Employee::~Employee() {};
void Employee::doWork()
{
	cout << "����Ҫ��ɾ�����������!";
}

Manager::~Manager() {};
Manager::Manager(int id, string name, int depId) :Worker(id, name, depId) {};
void Manager::doWork()
{
	cout << "����Ҫ����ϰ彻�������񣬲���Ա���´�����!";
}


Boss::~Boss() {};
Boss::Boss(int id, string name, int depId) :Worker(id, name, depId) {};
void Boss::doWork()
{
	cout << "����Ҫ����������˾!";
}
