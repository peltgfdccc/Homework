#include "student.h"

void load_bin()
{
	FILE *fp;
	char fname[20];
	int i=0,flag;
	printf("请输入文件名(如:stu.dat):");
	scanf("%s",fname);
	if((fp=fopen(fname,"rb"))==NULL)
	{
		printf("不能打开文件，文件保存失败！\n");
		return;
	}
	while(1)
	{
		flag=fread(&stu[i],sizeof(struct stu_type),1,fp);
		if(flag==0)
			break;
		i++;
	 } 
	 stu_num=i;
	 printf("从文件中成功读取%d条记录！\n",stu_num); 
	fclose(fp);
}

