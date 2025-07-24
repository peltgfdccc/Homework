#include "student.h"
struct stu_type stu[MAX_N];
int stu_num=0;
void add()
{
	int i=stu_num;
	printf("说明：依次输入学生信息，当学号输入为0时表示输入结束\n");
	while(1)
	{
		printf("请输入第%d个学生的信息\n",i+1);
		printf("请输入学号：");
		scanf("%s",stu[i].num);
		if(strcmp(stu[i].num,"0")==0)
			break;
		printf("请输入姓名：");
		scanf("%s",&stu[i].name);
		printf("请输入年龄：");
		scanf("%d",&stu[i].age);
		printf("请输入C语言成绩：");
		scanf("%d",&stu[i].c);
		printf("请输入数学成绩：");
		scanf("%d",&stu[i].math);
		printf("请输入英语成绩：");
		scanf("%d",&stu[i].en);
		stu[i].sum=stu[i].c+stu[i].math+stu[i].en;
		stu[i].ave=(float)stu[i].sum/3;
		i++;
	} 
	stu_num=i;
	printf("总共已输入%d个学生的信息\n",stu_num);
}
