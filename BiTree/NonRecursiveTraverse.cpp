#include <iostream>
#include <string.h>
#include <stack>
using namespace std;

class BiTree {//二叉树的链存储结构
public:
	char data;//数据域
	BiTree* lchild;//左孩子
	BiTree* rchild;//右孩子
public:
	BiTree();
};

BiTree::BiTree() {//初始化函数
	data = '\0';
	lchild = NULL;
	rchild = NULL;
}

stack<BiTree*> S;

void postOrderTraverse(BiTree* T) {//后序遍历
	if (T) {
		postOrderTraverse(T->lchild);
		postOrderTraverse(T->rchild);
		cout << T->data;
	}
}

void pushFisrt(char elem, BiTree* &T, BiTree* &p) {//由于没有头结点，所以第一个节点要特殊处理
	T->data = elem;
	S.push(T);
	p = T;
}
 
void pushCmd1(char elem, BiTree* &p) {//两种push操作的区别在于上一个操作时push还是pop
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

void popCmd1(BiTree* &p) {//两种pop操作的区别在于上一个操作时push还是pop
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

	bool pushOrPop = 1;//是push，则置1，是pop，则置0
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