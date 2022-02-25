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
	cout << "我需要完成经理交代的任务!";
}

Manager::~Manager() {};
Manager::Manager(int id, string name, int depId) :Worker(id, name, depId) {};
void Manager::doWork()
{
	cout << "我需要完成老板交代的任务，并向员工下达任务!";
}


Boss::~Boss() {};
Boss::Boss(int id, string name, int depId) :Worker(id, name, depId) {};
void Boss::doWork()
{
	cout << "我需要管理整个公司!";
}
