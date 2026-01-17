//查找指定学生信息的函数
#include "student.h"
void find()
{
	char str[15];
	printf("请输入要查找的学生学号：");
	scanf("%s",str);
	display_id(str);//显示该学生的信息
}
