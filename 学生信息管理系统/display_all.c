//��ʾ����ѧ����Ϣ�ĺ���
#include "student.h"
void display_all()
{
	int i;
	if(stu_num>0)//ѧ����������0
	{
		printf("ѧ��ѧ��\t����\t����\tC����\t��ѧ\tӢ��\t�ܷ�\ƽ����\n");
		for(i=0;i<stu_num;i++)
		printf("%-16s%s\t%d\t%d\t%d\t%d\t%d\t%5.1f\n",stu[i].num,stu[i].name,stu[i].age,stu[i].c,stu[i].math,stu[i].en,stu[i].sum,stu[i].ave);
	}
	else
		printf("ѧ����ϢΪ�գ�");
}
