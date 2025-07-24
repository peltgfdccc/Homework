#include<stdio.h>
void main()
{
	FILE *fp;
	char fname[20];
	int i=0,flag;
	printf("请输入文件名(如:stu.txt):");
	scanf("%s",fname);
	if((fp=fopen(fname,"r"))==NULL)
	{
		printf("不能打开文件，文件读取失败！\n");
		return;
	}
	while(1)
	{
		char c;
		flag=fscanf(fp,"%s",c);
		if(flag==EOF)
			break;
		i++;
	 } 
	 int a=i;
	 printf("从文件中成功读取%d条记录！\n",i); 
	fclose(fp);
}
