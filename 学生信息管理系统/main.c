#include "student.h"
void main() 
{
	int menu_choose();
	while(1)
	{
		int choice=menu_choose();
		switch(choice)
		{
			case 1: add();	break;
			case 2: display_all();	break;
			case 3: modify();	break;
			case 4: del();	break;
			case 5: find();	break;
			case 6: compute(); break;
			case 7: sort(); break;
			case 8: save_txt(); break;
			case 9:	load_txt();	break;
			case 10: save_bin();	break;
			case 11: load_bin();	break;
			case 12: exit(0); break;
		}
	}
}

int menu_choose()
{
	int choice;
	printf("\n           ��ӭʹ��ѧ����Ϣ����ϵͳ\n");
	printf("------------------------------------------------\n");
	printf("1.���ѧ����Ϣ    2.��ʾѧ����Ϣ\n");
	printf("3.�޸�ѧ����Ϣ    4.ɾ��ѧ����Ϣ\n");
	printf("5.����ѧ����Ϣ    6.ͳ�Ʋ�������������߷ֺ�ƽ����\n");
	printf("7.���ܷ�����      8.�������ļ�<�ı���ʽ>\n");
	printf("9.���ļ�����<�ı���ʽ>  10.�������ļ�<�����Ʒ�ʽ>\n");
	printf("11.���ļ�����<�����Ʒ�ʽ>  12.�˳�����\n");
	printf("------------------------------------------------\n");
	printf("��ѡ����ģ�飬��������1-12:");
	while(1)
	{
		scanf("%d",&choice);
		if(choice>=1&&choice<=12) break;
		else printf("�������ֲ���ȷ��������1-12��");
	}
	
	return choice; 
}

