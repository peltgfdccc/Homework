#include "student.h"

void save_bin()
{
	FILE *fp;
	char fname[20];
	int i;
	printf("请输入文件名(如:stu.dat):");
	scanf("%s",fname);
	if((fp=fopen(fname,"wb"))==NULL)
	{
		printf("不能打开文件，文件保存失败！\n");
		return;
	}
	fwrite(stu,sizeof(struct stu_type),stu_num,fp);
	printf("文件保存成功！\n");
	fclose(fp);
}

