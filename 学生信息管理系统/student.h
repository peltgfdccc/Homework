#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100


struct stu_type{
	char num[15];
	char name[10];
	int age;
	int c;
	int math;
	int en;
	int sum;
	float ave;
};

extern int stu_num;
extern struct stu_type stu[];

void add();
void display_all();
void modify();
void del();
void find();	
void compute();
void sort();
void save_txt(); 
void load_txt();	
void save_bin();	
void load_bin();
int display_id(char str[]);

