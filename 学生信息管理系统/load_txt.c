#include<stdio.h>
void main()
{
	FILE *fp;
	char fname[20];
	int i=0,flag;
	printf("�������ļ���(��:stu.txt):");
	scanf("%s",fname);
	if((fp=fopen(fname,"r"))==NULL)
	{
		printf("���ܴ��ļ����ļ���ȡʧ�ܣ�\n");
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
	 printf("���ļ��гɹ���ȡ%d����¼��\n",i); 
	fclose(fp);
}
