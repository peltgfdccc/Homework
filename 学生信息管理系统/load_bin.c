#include "student.h"

void load_bin()
{
	FILE *fp;
	char fname[20];
	int i=0,flag;
	printf("�������ļ���(��:stu.dat):");
	scanf("%s",fname);
	if((fp=fopen(fname,"rb"))==NULL)
	{
		printf("���ܴ��ļ����ļ�����ʧ�ܣ�\n");
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
	 printf("���ļ��гɹ���ȡ%d����¼��\n",stu_num); 
	fclose(fp);
}

