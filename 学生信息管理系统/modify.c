//�޸�ѧ����Ϣ�ĺ���
#include"student.h"
void modify()
{
	char str[ 15],m;
	int i;
	printf("������Ҫ�޸ĵ�ѧ��ѧ�ţ�");
	scanf("%s",str);
	i=display_id(str);//���Ҳ���ʾ��ѧ������Ϣ��iΪ��ѧ���������±�
	if(i!=-1)//i!=-1������display(�������и�ѧ�����ҵ�
	{
		printf("ȷ���޸ĸ�ѧ������Ϣ�𣿣�y/n)��");
		m=getche();
		if(m=='y' || m=='Y')	//���޸�
		{
			printf("\n�����������ѧ������Ϣ\n");
			printf("������ѧ�ţ�");
			scanf("%s",stu[i].num);
			printf("������������");
			scanf("%s",stu[i].name);
			printf("���������䣺");
			scanf("%d",&stu[i].age);
			printf("������C���Գɼ���");
			scanf("%d",&stu[i].c);
			printf("��������ѧ�ɼ���");
			scanf("%d",&stu[i].math);
			printf("������Ӣ��ɼ���");
			scanf("%d",&stu[i].en);
			stu[i].sum=stu[i].c+stu[i].math+stu[i].en;
			stu[i].ave=(float)stu[i].sum/3;
		}
	}
}
