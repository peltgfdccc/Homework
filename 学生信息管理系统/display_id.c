//��ʾָ��ѧ����Ϣ�ĺ���
#include"student.h"
int display_id(char str[ ])
{
	int i,id=-1;
	for(i=0;i<stu_num;i++)
	if(strcmp(str,stu[i].num)==0)//����
	{
		//��ʾ��ѧ������Ϣ
		printf("ѧ��ѧ��\t����\t����\tC����\t��ѧ\tӢ��\t�ܷ�\tƽ����\n");
		printf("%-16s%s\t%d\t%d\t%d\t%d\t%d\t%5.1f\n",stu[i].num,stu[i].name,stu[i].age,stu[i].c,stu[i].math,
				stu[i].en,stu[i].sum,stu[i].ave);
		id=i;//����ѧ���������±긳��id
	}
	if(id==-1)
	printf("û���ҵ�����������ѧ��\n");
	return id;
}
