//显示指定学生信息的函数
#include"student.h"
int display_id(char str[ ])
{
	int i,id=-1;
	for(i=0;i<stu_num;i++)
	if(strcmp(str,stu[i].num)==0)//查找
	{
		//显示该学生的信息
		printf("学生学号\t姓名\t年龄\tC语言\t数学\t英语\t总分\t平均分\n");
		printf("%-16s%s\t%d\t%d\t%d\t%d\t%d\t%5.1f\n",stu[i].num,stu[i].name,stu[i].age,stu[i].c,stu[i].math,
				stu[i].en,stu[i].sum,stu[i].ave);
		id=i;//将该学生的数组下标赋给id
	}
	if(id==-1)
	printf("没有找到符合条件的学生\n");
	return id;
}
