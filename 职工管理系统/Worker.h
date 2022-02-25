#pragma once
#include <string>
using namespace std;
class Worker
{
public:
	Worker(int id, string name, int dptId);
	~Worker();
	void showId();
	void showName();
	void showDepId();
	virtual void doWork() = 0;
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
	virtual void doWork();
private:

};

class Manager:public Worker
{
public:
	Manager(int id, string name, int depId);
	~Manager();
	virtual void doWork();

private:

};

class Boss:public Worker
{
public:
	Boss(int id, string name, int depId);
	~Boss();
	virtual void doWork();
private:

};
