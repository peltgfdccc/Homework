//ɾ������������Ϣ�ĺ���
#include "student.h"
void del()
{
	char str[15],m;
	int i,j;
	printf("������Ҫɾ����ѧ��ѧ�ţ�");
	scanf("%s",str);
	i=display_id (str);//���Ҳ���ʾ��ѧ������Ϣ��iΪ��ѧ���������±�
	if(i!=-1)			//i��=-1������ѧ�����ҵ�
	{
		printf("ȷ��ɾ����ѧ������Ϣ��(y/n):");
		m=getche();
		if(m=='y'||m=='Y')
		{
			stu_num--;				//ѧ���������� 1
			for(j=i;j<stu_num;j++)	//����ѧ�����������ѧ��ǰ��һλ
				stu[j]=stu[j+1];
			printf("\n��¼ɾ���ɹ���\n");
		}
	}
}
