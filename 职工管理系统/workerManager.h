#pragma once //防止头文件重复包含
class WorkerManager
{
public:
	WorkerManager();
	~WorkerManager();
	void showMenu();
	void exitSystem(); 
	bool addEmployee();
	void showEmployees();
	void delEmployee();
	void modifyEmployee();
	void searchEmployee();
	void sortEmployees();
	void emptyAll();
private:
	int m_N=0;//职工人数
	char m_employeesFile[100];//职工信息存放处
};