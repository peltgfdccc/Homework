#include "student.h"

void sort()
{
	int i,j;
	struct stu_type temp;
	for(i=1;i<=stu_num-1;i++)
		for(j=0;j<stu_num-1;j++)
		if(stu[j].sum<stu[j].sum)
		{
			temp=stu[j];
			stu[j]=stu[j+1];
			stu[j+1]=temp;	
		 } 
	printf("排序结果如下：\n");
	printf("名次\t学生学号\t姓名\t年龄\tC语言\t数学\t英语\t总分\t平均分\n");
	for(i=0;i<stu_num;i++)
	{
		printf("%d\t%-16s%s\t%d\t%d\t%d\t%d\t%d\t%5.1f\n",i+1,stu[i].num,stu[i].name,stu[i].age,stu[i].c,stu[i].math,stu[i].en,stu[i].sum,stu[i].ave);
	}
}

