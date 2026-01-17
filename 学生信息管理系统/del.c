//删际拍走字生信息的函数
#include "student.h"
void del()
{
	char str[15],m;
	int i,j;
	printf("请输入要删除的学生学号：");
	scanf("%s",str);
	i=display_id (str);//查找并显示该学生的信息，i为该学生的数组下标
	if(i!=-1)			//i！=-1表明该学生已找到
	{
		printf("确认删除该学生的信息吗？(y/n):");
		m=getche();
		if(m=='y'||m=='Y')
		{
			stu_num--;				//学生总人数减 1
			for(j=i;j<stu_num;j++)	//将该学生后面的所有学生前移一位
				stu[j]=stu[j+1];
			printf("\n记录删除成功！\n");
		}
	}
}
