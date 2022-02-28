#include <iostream>
#include <string>
#include "workerManager.h"
#include "Worker.h"
using namespace std;


int main()
{
	WorkerManager workerManager("employees.txt");
	int op;
	while (true)
	{
		workerManager.showMenu();
		cin >> op;
		switch (op)
		{
		case 0://�˳�ϵͳ
			workerManager.exitSystem();
			break;
		case 1://����ְ��
			workerManager.batchAddEmployees();
			break;
		case 2://��ʾְ��
			workerManager.showEmployees();
			break;
		case 3://ɾ��ְ��
			int delType;
			cout << "��ְ�����ɾ����������0����ְ������ɾ����������1��" << endl;
			cin >> delType;
			if (delType == 0)
			{
				int id;
				cout << "������ְ����ţ�" << endl;
				cin >> id;
				workerManager.delEmployee(id);
			}
			else if(delType==1)
			{
				string name;
				cout << "������ְ��������" << endl;
				cin >> name;
				workerManager.delEmployee(-1,name.c_str());
			}
			else
			{
				cout << "�������" << endl;
			}
			break;
		case 4://�޸�ְ��
			workerManager.modifyEmployee();
			break;
		case 5://����ְ��
			workerManager.searchEmployee();
			break;
		case 6://����ְ��
			workerManager.sortEmployees();
			break;
		case 7://����ĵ�
			workerManager.emptyAll();
			break;
		default:
			cout << "��������!" << endl;
		}
		system("pause");
		system("cls");
	}
	return 0;
}