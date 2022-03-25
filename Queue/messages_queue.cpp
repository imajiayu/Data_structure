#include <iostream>
#include <queue>
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

BiTree* preCreate() {//先序递归建立二叉树
	BiTree* T;
	char elem;
	cin >> elem;
	if (elem == '#')//节点为空
		T = NULL;
	else {
		T = (BiTree*)malloc(sizeof(BiTree));
		T->data = elem;

		T->lchild = preCreate();//递归建立左子树
		T->rchild = preCreate();//递归建立右子树
	}
	return T;
}

void preOrderTraverse(BiTree* T) {//先序遍历
	if (T) {
		cout << T->data;
		preOrderTraverse(T->lchild);
		preOrderTraverse(T->rchild);
	}
}


void inOrderTraverse(BiTree* T) {//中序遍历
	if (T) {
		inOrderTraverse(T->lchild);
		cout << T->data;
		inOrderTraverse(T->rchild);
	}
}

void postOrderTraverse(BiTree* T) {//后序遍历
	if (T) {
		postOrderTraverse(T->lchild);
		postOrderTraverse(T->rchild);
		cout << T->data;
	}
}

void levelOrderTraverse(BiTree* T) {//层次遍历
	BiTree* p;
	queue<BiTree*> Q;
	if (T) {
		Q.push(T);
		while (!Q.empty()) {
			p = Q.front();
			cout << p->data;
			Q.pop();
			if (p->lchild)
				Q.push(p->lchild);
			if (p->rchild)
				Q.push(p->rchild);
		}
	}
}

void prtbtree(BiTree* p, int cur)//逆中序遍历，逆时针旋转90度输出二叉树
{
	if (p)
	{
		prtbtree(p->rchild, cur + 1);
		for (int i = 0; i < cur; i++)
			cout << "     ";
		cout << p->data;
		cout << '\n';
		prtbtree(p->lchild, cur + 1);
	}
}

int main() {
	BiTree* T = preCreate();
	preOrderTraverse(T);
	cout << '\n';
	inOrderTraverse(T);
	cout << '\n';
	postOrderTraverse(T);
	cout << '\n';
	levelOrderTraverse(T);
	cout << '\n';
	prtbtree(T, 0);
	return 0;
}