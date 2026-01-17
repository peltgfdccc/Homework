#include "student.h"
void main() 
{
	int menu_choose();
	while(1)
	{
		int choice=menu_choose();
		switch(choice)
		{
			case 1: add();	break;
			case 2: display_all();	break;
			case 3: modify();	break;
			case 4: del();	break;
			case 5: find();	break;
			case 6: compute(); break;
			case 7: sort(); break;
			case 8: save_txt(); break;
			case 9:	load_txt();	break;
			case 10: save_bin();	break;
			case 11: load_bin();	break;
			case 12: exit(0); break;
		}
	}
}

int menu_choose()
{
	int choice;
	printf("\n           欢迎使用学生信息管理系统\n");
	printf("------------------------------------------------\n");
	printf("1.添加学生信息    2.显示学生信息\n");
	printf("3.修改学生信息    4.删除学生信息\n");
	printf("5.查找学生信息    6.统计不及格人数，最高分和平均分\n");
	printf("7.按总分排序      8.保存至文件<文本方式>\n");
	printf("9.从文件读入<文本方式>  10.保存至文件<二进制方式>\n");
	printf("11.从文件读入<二进制方式>  12.退出程序\n");
	printf("------------------------------------------------\n");
	printf("请选择功能模块，输入数字1-12:");
	while(1)
	{
		scanf("%d",&choice);
		if(choice>=1&&choice<=12) break;
		else printf("输入数字不正确，请重输1-12：");
	}
	
	return choice; 
}

