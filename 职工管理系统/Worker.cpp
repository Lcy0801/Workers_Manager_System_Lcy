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
string Worker::getName()
{
	return m_Name;
}

int Worker::getId() 
{
	return m_Id;
}

int Worker::getDepId()
{
	return m_DepId;
}


Employee::Employee(int id, string name, int depId) :Worker(id, name, depId) {};
Employee::~Employee() {};
string Employee::doWork()
{
	return "����Ҫ��ɾ�����������!";
}

Manager::~Manager() {};
Manager::Manager(int id, string name, int depId) :Worker(id, name, depId) {};
string Manager::doWork()
{
	return "����Ҫ����ϰ彻�������񣬲���Ա���´�����!";
}


Boss::~Boss() {};
Boss::Boss(int id, string name, int depId) :Worker(id, name, depId) {};
string Boss::doWork()
{
	return "����Ҫ����������˾!";
}
