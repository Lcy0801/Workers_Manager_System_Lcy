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
		case 0://退出系统
			workerManager.exitSystem();
			break;
		case 1://增加职工
			break;
		case 2://显示职工
			break;
		case 3://删除职工
			break;
		case 4://修改职工
			break;
		case 5://查找职工
			break;
		case 6://排序职工
			break;
		case 7://清空文档
			break;
		default:
			cout << "操作错误!" << endl;
		}
		system("cls");
	}
	return 0;
}