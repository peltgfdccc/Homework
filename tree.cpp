#include<iostream>
#include<stdlib.h>
#include<queue>
#include <fstream>  
#include <cstdlib> 
using namespace std;
typedef struct Node{
	char data;
	struct Node* left;
	struct Node* right;
}BiNode,*BiTree;
 
void createTree(BiTree *bt, std::ifstream &inFile) {  
    char c;  
    inFile >> c;  
    if (inFile.fail()) { // ����ļ��Ƿ��ѽ������ȡʧ��  
        *bt = NULL;  
        return;  
    }  
    if (c == '#') {  
        *bt = NULL;  
    } else {  
        *bt = (BiTree)malloc(sizeof(BiNode)); 
        (*bt)->data = c;  
        createTree(&(*bt)->left, inFile);  
        createTree(&(*bt)->right, inFile);  
    }  
} //���������� 

//���ʲ���������
void visit(BiTree T){
	FILE *outputFile = fopen("output.txt", "w");
	cout<<T->data<<" ";
	fputc(T->data ,outputFile);
} 
 
//����������ݹ飩 
void PreOrder(BiTree T){
	if(T){
		visit(T);
		PreOrder(T->left);
		PreOrder(T->right);
	}
} 

//����������ǵݹ飩
void PreOrderNRec(BiTree T){
	FILE *outputFile = fopen("output.txt", "w");
	BiTree stack[100], node;
	int k = -1;
 
	if (T == NULL){
		printf("tree is empty-- \n");
		return;
	}
	else{
		k++;
		// ����һ��ջ
		stack[k] = T; // �����ڵ���ջ
		while (k > -1){
			//��ջ
			node = stack[k--];
			fputc(node->data ,outputFile);
			printf("%c ", node->data);
			// �Ȱ��������Ž�ȥ��ջ���Ƚ�ȥ���������������������ȳ�
			if (node->right != NULL){
				stack[++k] = node->right;
			}
			if (node->left != NULL){
				stack[++k] = node->left;
			}
 
		}
 
	}
}
 
//����������ݹ飩
void InOrder(BiTree T){
	if(T){
		InOrder(T->left);
		visit(T);
		InOrder(T->right);
	}
} 

//����������ǵݹ飩
void InOrderNRec(BiTree T){
	FILE *outputFile = fopen("output.txt", "w");
	BiTree stack[100], node;
	int top = 0;
	// �ж����Ƿ�Ϊ��
	if (T == NULL){
		printf("tree is empty-- \n");
		return;
	}
	node = T;
 
	while (node != NULL || top > 0){
 
		// �����е��������ڵ���ջ
		while (node != NULL){
			stack[++top] = node;
			node = node->left;
		}
		//  ����ҽڵ�Ϊ�յĻ���ִ���������
		node = stack[top--];
		fputc(node->data ,outputFile);
		printf("%c ", node->data);
 
		// ɨ���ҽڵ�
		node = node->right;
	}
 
}
 
//����������ݹ飩
void PostOrder(BiTree T){
	if(T){
		PostOrder(T->left);
		PostOrder(T->right);
		visit(T);
	}
} 

//����������ǵݹ飩
 
void backOrderNRec(BiTree T){
	FILE *outputFile = fopen("output.txt", "w");
	BiTree stack[100], node;
	int top = 0;
	int count = 0;
	char array[100]; // ʹ��һ���������������ݣ������������ķ�ת
 
	if (T == NULL){
		printf("tree is empty-- \n");
		return;
	}
	else{
		top++;
		// ����һ��ջ
		stack[top] = T; // �����ڵ���ջ
		while (top > 0){
			//��ջ
			node = stack[top--];
			array[count++] = node->data; // ���䱣����һ�����鵱��
 
			// �Ȱ��������Ž�ȥ��ջ���Ƚ�ȥ���������������������ȳ�
			if (node->left != NULL){
				stack[++top] = node->left;  // ��ջ
			}
			if (node->right != NULL){
				stack[++top] = node->right;
			}
 
		}
	}
	// ��ת���飬���
	for (int i = count-1; i >= 0; i--){
		printf("%c ", array[i]);
		fputc(array[i] ,outputFile);
	}
 
} 
 
//����������ǵݹ飩 
void LevelOrder(BiTree T){
	FILE *outputFile = fopen("output.txt", "w");
	if(T==NULL) return ;
	queue<BiTree>que;
	que.push(T);
	while(!que.empty()){
		BiTree ptr=que.front();
		cout<<ptr->data<<" ";
		fputc(ptr->data ,outputFile);
		que.pop();
		if(ptr->left!=NULL)
		  que.push(ptr->left);
		if(ptr->right!=NULL)
		  que.push(ptr->right);
	}
} 

int main(){
	FILE *inputFile = fopen("input.txt", "r");  
    FILE *outputFile = fopen("output.txt", "w");
    std::ifstream inFile("input.txt"); // �滻Ϊ����ļ���  
    if (!inFile.is_open()) {  
        std::cerr << "Failed to open file." << std::endl;  
        return 1;  
    }  
	BiTree T;
	createTree(&T,inFile);
	cout<<"����������ѡ�������ʽ"<<endl;
	cout<<"1.�������(�ݹ��㷨)      2.�������(�ݹ��㷨)"<<endl;
	cout<<"3.�������(�ݹ��㷨)      4.�������"<<endl;
	cout<<"5.�������(�ǵݹ��㷨)    6.�������(�ǵݹ��㷨)"<<endl;
	cout<<"7.�������(�ǵݹ��㷨)    8.�˳�����"<<endl;
	while(1){
		int num;
		cin>>num;
		if(num<1||num>8){
			cout<<"number is wrong"<<endl;
			continue;
		}
		switch(num){
			case 1:PreOrder(T);cout<<endl;break;
			case 2:InOrder(T);cout<<endl;break;
			case 3:PostOrder(T);cout<<endl;break;
			case 4:LevelOrder(T);cout<<endl;break;
			case 5:PreOrderNRec(T);cout<<endl; break;
			case 6:InOrderNRec(T);cout<<endl;break;
			case 7:backOrderNRec(T);cout<<endl;break;
			case 8:exit(0); break;
		} 
	} 
} 
