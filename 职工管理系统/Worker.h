#pragma once
#include <string>
using namespace std;
class Worker
{
public:
	Worker(int id, string name, int dptId);
	~Worker();
	int getId();
	string getName();
	int getDepId();
	virtual string doWork() = 0;
private:
	int m_Id;
	string m_Name;
	int m_DepId;
};

class Employee:public Worker
{
public:
	Employee(int id, string name, int depId);
	~Employee();
	virtual string doWork();
private:

};

class Manager:public Worker
{
public:
	Manager(int id, string name, int depId);
	~Manager();
	virtual string doWork();

private:

};

class Boss:public Worker
{
public:
	Boss(int id, string name, int depId);
	~Boss();
	virtual string doWork();
private:

};
