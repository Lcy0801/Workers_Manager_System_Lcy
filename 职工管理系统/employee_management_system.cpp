#include <iostream>
#include <string>
#include "workerManager.h"
#include "Worker.h"
using namespace std;


int main()
{
	WorkerManager workerManager;
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
			break;
		case 2://��ʾְ��
			break;
		case 3://ɾ��ְ��
			break;
		case 4://�޸�ְ��
			break;
		case 5://����ְ��
			break;
		case 6://����ְ��
			break;
		case 7://����ĵ�
			break;
		default:
			cout << "��������!" << endl;
		}
		system("cls");
	}
	return 0;
}