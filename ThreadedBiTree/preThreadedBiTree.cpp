#define LINK 0
#define THREAD 1;
#include <iostream>
#include <queue>
using namespace std;

class BiTree {//二叉树的链存储结构
public:
	char data;//数据域
	int Ltag;
	int Rtag;
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

void preOrderTraverse(BiTree* T) {//先序遍历已经先序线索化的二叉树
	if (T == NULL)
		return;
	BiTree* p = T;
	while (p) {
		while (p->Ltag == LINK) {
			cout << p->data;
			p = p->lchild;
		}
		cout << p->data;
		p = p->rchild;
	}
}

void prtbtree(BiTree* p, int cur)//逆中序遍历，逆时针旋转90度输出二叉树
{
	if (p)
	{
		prtbtree(p->rchild, cur + 1);
		for (int i = 0; i < cur; i++)
			cout << "     ";
		cout << p->data<<p->Ltag<<p->Rtag;
		cout << '\n';
		prtbtree(p->lchild, cur + 1);
	}
}

BiTree* pre=NULL;

void preOrderThreading(BiTree* T) {//先序线索化二叉树
	if (T == NULL)
		return;
	if (T->lchild == NULL) {
		T->lchild = pre;
		T->Ltag = THREAD;
	}
	if (pre != NULL && pre->rchild == NULL) {
		pre->rchild = T;
		pre->Rtag = THREAD;
	}
	pre = T;
	if (T->Ltag==LINK)
		preOrderThreading(T->lchild);
	if (T->Rtag==LINK)
		preOrderThreading(T->rchild);
}

void setZero(BiTree* T) {//标志位置0
	if (T) {
		T->Ltag = T->Rtag = 0;
		setZero(T->lchild);
		setZero(T->rchild);
	}
}

void setLRtag(BiTree* T) {//标志位置应该置的数
	if (T) {
		if (T->lchild == NULL)
			T->Ltag = THREAD;
		if (T->rchild == NULL)
			T->Rtag = THREAD;
		setLRtag(T->lchild);
		setLRtag(T->rchild);
	}
}

int main() {
	BiTree* T = preCreate();
	setZero(T);
	setLRtag(T);
	prtbtree(T, 0);
	setZero(T);
	preOrderThreading(T);
	preOrderTraverse(T);
	return 0;
}