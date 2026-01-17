#include "student.h"

void compute()
{
	int i,n=0,max=0,sum=0;
	for(i=0;i<stu_num;i++)
	{
		if(stu[i].c<60) n++;
		if(max<stu[i].c) max=stu[i].c;
		sum=sum+stu[i].c;
	}
	printf("      C语言统计结果如下：\n");
	printf("不及格人数\t最高分\t平均分\t\t\n");
	printf("       %d     \t  %d  \t%5.2f\n",n,max,(float)sum/stu_num);
	 
}
