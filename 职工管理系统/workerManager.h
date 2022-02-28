#pragma once //��ֹͷ�ļ��ظ�����
#include <string>
using namespace std;
class WorkerManager
{
private:
	string m_employeesFile;//ְ����Ϣ��Ŵ�
public:
	WorkerManager(string employeesFile);
	~WorkerManager();
	void showMenu();
	void exitSystem(); 
	void addEmployee();
	void batchAddEmployees();
	void showEmployees();
	void delEmployee(int id=-1,const char * name="");
	void modifyEmployee();
	void searchEmployee();
	void sortEmployees();
	void emptyAll();
	bool idExists(int id);
	bool nameExists(const char * name);
};