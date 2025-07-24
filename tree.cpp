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
    if (inFile.fail()) { // 检查文件是否已结束或读取失败  
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
} //创建二叉树 

//访问并输出根结点
void visit(BiTree T){
	FILE *outputFile = fopen("output.txt", "w");
	cout<<T->data<<" ";
	fputc(T->data ,outputFile);
} 
 
//先序遍历（递归） 
void PreOrder(BiTree T){
	if(T){
		visit(T);
		PreOrder(T->left);
		PreOrder(T->right);
	}
} 

//先序遍历（非递归）
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
		// 仿照一个栈
		stack[k] = T; // 将根节点入栈
		while (k > -1){
			//出栈
			node = stack[k--];
			fputc(node->data ,outputFile);
			printf("%c ", node->data);
			// 先把右子树放进去，栈是先进去后出，所以下面的左子树先出
			if (node->right != NULL){
				stack[++k] = node->right;
			}
			if (node->left != NULL){
				stack[++k] = node->left;
			}
 
		}
 
	}
}
 
//中序遍历（递归）
void InOrder(BiTree T){
	if(T){
		InOrder(T->left);
		visit(T);
		InOrder(T->right);
	}
} 

//中序遍历（非递归）
void InOrderNRec(BiTree T){
	FILE *outputFile = fopen("output.txt", "w");
	BiTree stack[100], node;
	int top = 0;
	// 判断树是否为空
	if (T == NULL){
		printf("tree is empty-- \n");
		return;
	}
	node = T;
 
	while (node != NULL || top > 0){
 
		// 将所有的左子树节点入栈
		while (node != NULL){
			stack[++top] = node;
			node = node->left;
		}
		//  如果右节点为空的话，执行下列语句
		node = stack[top--];
		fputc(node->data ,outputFile);
		printf("%c ", node->data);
 
		// 扫描右节点
		node = node->right;
	}
 
}
 
//后序遍历（递归）
void PostOrder(BiTree T){
	if(T){
		PostOrder(T->left);
		PostOrder(T->right);
		visit(T);
	}
} 

//后序遍历（非递归）
 
void backOrderNRec(BiTree T){
	FILE *outputFile = fopen("output.txt", "w");
	BiTree stack[100], node;
	int top = 0;
	int count = 0;
	char array[100]; // 使用一个数组来保存数据，方便最后数组的反转
 
	if (T == NULL){
		printf("tree is empty-- \n");
		return;
	}
	else{
		top++;
		// 仿照一个栈
		stack[top] = T; // 将根节点入栈
		while (top > 0){
			//出栈
			node = stack[top--];
			array[count++] = node->data; // 将其保存在一个数组当中
 
			// 先把右子树放进去，栈是先进去后出，所以下面的左子树先出
			if (node->left != NULL){
				stack[++top] = node->left;  // 入栈
			}
			if (node->right != NULL){
				stack[++top] = node->right;
			}
 
		}
	}
	// 反转数组，输出
	for (int i = count-1; i >= 0; i--){
		printf("%c ", array[i]);
		fputc(array[i] ,outputFile);
	}
 
} 
 
//层序遍历（非递归） 
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
    std::ifstream inFile("input.txt"); // 替换为你的文件名  
    if (!inFile.is_open()) {  
        std::cerr << "Failed to open file." << std::endl;  
        return 1;  
    }  
	BiTree T;
	createTree(&T,inFile);
	cout<<"输入数字以选择遍历方式"<<endl;
	cout<<"1.先序遍历(递归算法)      2.中序遍历(递归算法)"<<endl;
	cout<<"3.后序遍历(递归算法)      4.层序遍历"<<endl;
	cout<<"5.先序遍历(非递归算法)    6.中序遍历(非递归算法)"<<endl;
	cout<<"7.后序遍历(非递归算法)    8.退出程序"<<endl;
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
