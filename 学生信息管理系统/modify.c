//修改学生信息的函数
#include"student.h"
void modify()
{
	char str[ 15],m;
	int i;
	printf("请输入要修改的学生学号：");
	scanf("%s",str);
	i=display_id(str);//查找并显示该学生的信息，i为该学生的数组下标
	if(i!=-1)//i!=-1表明在display(）函数中该学生已找到
	{
		printf("确认修改该学生的信息吗？（y/n)：");
		m=getche();
		if(m=='y' || m=='Y')	//再修改
		{
			printf("\n请重新输入该学生的信息\n");
			printf("请输入学号：");
			scanf("%s",stu[i].num);
			printf("请输入姓名：");
			scanf("%s",stu[i].name);
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
		}
	}
}
