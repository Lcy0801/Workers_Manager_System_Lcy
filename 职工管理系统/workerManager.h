#pragma once //��ֹͷ�ļ��ظ�����
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
	int m_N=0;//ְ������
	char m_employeesFile[100];//ְ����Ϣ��Ŵ�
};