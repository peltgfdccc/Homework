#include "student.h"

void save_bin()
{
	FILE *fp;
	char fname[20];
	int i;
	printf("�������ļ���(��:stu.dat):");
	scanf("%s",fname);
	if((fp=fopen(fname,"wb"))==NULL)
	{
		printf("���ܴ��ļ����ļ�����ʧ�ܣ�\n");
		return;
	}
	fwrite(stu,sizeof(struct stu_type),stu_num,fp);
	printf("�ļ�����ɹ���\n");
	fclose(fp);
}

