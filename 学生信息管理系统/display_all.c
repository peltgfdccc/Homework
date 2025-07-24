//显示所有学生信息的函数
#include "student.h"
void display_all()
{
	int i;
	if(stu_num>0)//学生人数大于0
	{
		printf("学生学号\t姓名\t年龄\tC语言\t数学\t英语\t总分\平均分\n");
		for(i=0;i<stu_num;i++)
		printf("%-16s%s\t%d\t%d\t%d\t%d\t%d\t%5.1f\n",stu[i].num,stu[i].name,stu[i].age,stu[i].c,stu[i].math,stu[i].en,stu[i].sum,stu[i].ave);
	}
	else
		printf("学生信息为空！");
}
