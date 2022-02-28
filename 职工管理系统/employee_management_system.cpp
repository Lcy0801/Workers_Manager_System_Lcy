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
		case 0://退出系统
			workerManager.exitSystem();
			break;
		case 1://增加职工
			workerManager.batchAddEmployees();
			break;
		case 2://显示职工
			workerManager.showEmployees();
			break;
		case 3://删除职工
			int delType;
			cout << "按职工编号删除，请输入0；按职工姓名删除，请输入1；" << endl;
			cin >> delType;
			if (delType == 0)
			{
				int id;
				cout << "请输入职工编号：" << endl;
				cin >> id;
				workerManager.delEmployee(id);
			}
			else if(delType==1)
			{
				string name;
				cout << "请输入职工姓名：" << endl;
				cin >> name;
				workerManager.delEmployee(-1,name.c_str());
			}
			else
			{
				cout << "输入错误" << endl;
			}
			break;
		case 4://修改职工
			workerManager.modifyEmployee();
			break;
		case 5://查找职工
			workerManager.searchEmployee();
			break;
		case 6://排序职工
			workerManager.sortEmployees();
			break;
		case 7://清空文档
			workerManager.emptyAll();
			break;
		default:
			cout << "操作错误!" << endl;
		}
		system("pause");
		system("cls");
	}
	return 0;
}