#include <iostream>
#include <string.h>
#include <stack>
using namespace std;

class BiTree {//�����������洢�ṹ
public:
	char data;//������
	BiTree* lchild;//����
	BiTree* rchild;//�Һ���
public:
	BiTree();
};

BiTree::BiTree() {//��ʼ������
	data = '\0';
	lchild = NULL;
	rchild = NULL;
}

stack<BiTree*> S;

void postOrderTraverse(BiTree* T) {//�������
	if (T) {
		postOrderTraverse(T->lchild);
		postOrderTraverse(T->rchild);
		cout << T->data;
	}
}

void pushFisrt(char elem, BiTree* &T, BiTree* &p) {//����û��ͷ��㣬���Ե�һ���ڵ�Ҫ���⴦��
	T->data = elem;
	S.push(T);
	p = T;
}
 
void pushCmd1(char elem, BiTree* &p) {//����push����������������һ������ʱpush����pop
	BiTree* newNode = (BiTree*)malloc(sizeof(BiTree));
	newNode->data = elem;
	p->lchild = newNode;
	S.push(newNode);
	p = p->lchild;
}

void pushCmd2(char elem, BiTree*& p) {
	BiTree* newNode = (BiTree*)malloc(sizeof(BiTree));
	newNode->data = elem;
	p->rchild = newNode;
	S.push(newNode);
	p = p->rchild;
}

void popCmd1(BiTree* &p) {//����pop����������������һ������ʱpush����pop
	p->lchild = NULL;
	p = S.top();
	S.pop();
}

void popCmd2(BiTree*& p) {
	p->rchild = NULL;
	p = S.top();
	S.pop();
}


int main() {
	BiTree* T = (BiTree*)malloc(sizeof(BiTree));
	T->lchild = NULL;
	T->rchild = NULL;
	BiTree* p=NULL;

	bool pushOrPop = 1;//��push������1����pop������0
	int nodeNum = 0;
	cin >> nodeNum;
	char cmd0[10], elem0;
	cin >> cmd0 >> elem0;
	pushFisrt(elem0, T, p);
	pushOrPop = 1;
	for (int i = 0; i < 2 * nodeNum-1; i++) {
		char cmd[10];
		cin >> cmd;
		if (!strcmp(cmd, "push")) {
			char elem;
			cin >> elem;
			if (pushOrPop)
				pushCmd1(elem, p);
			else pushCmd2(elem, p);
			pushOrPop = 1;
		}
		if (!strcmp(cmd, "pop")) {
			if (!pushOrPop)
				popCmd2(p);
			else popCmd1(p);
			pushOrPop = 0;
		}
	}
	p->rchild = NULL;
	postOrderTraverse(T);
}