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

BiTree* first(BiTree* T) {//中序遍历线索化二叉树的第一个节点是一直走到最左端的节点
	BiTree* p=T;
	if (p == NULL)
		return NULL;
	while (p->Ltag == LINK)
		p = p->lchild;
	return p;
}

BiTree* next(BiTree* T) {//中序遍历线索二叉树的下一个节点是右子树的第一个节点或后继节点
	BiTree* p=T;
	if (p->Rtag == 0)
		return first(p->rchild);
	else return p->rchild;
}

void inOrderTraverse(BiTree* T) {//中序遍历已经中序线索化的二叉树
	for (BiTree* p = first(T); p != NULL; p = next(p)) 
		cout << p->data;
	cout << endl;
}

void found(BiTree* T, char target) {//遍历查找线索化二叉树，用pre指针记录前驱节点
	BiTree* pre=NULL;
	for (BiTree* p = first(T); p != NULL; p = next(p)) {
		if (p->data == target) {
			cout << "succ is ";
			if (next(p) == NULL)
				cout << "NULL" << endl;
			else cout << next(p)->data << next(p)->Rtag << endl;

			cout << "prev is ";
			if (pre == NULL)
				cout << "NULL" << endl;
			else cout << pre->data << pre->Ltag << endl;

			return;
		}
		pre = p;
	}
	cout << "Not found";
}

BiTree* pre = NULL;

void inOrderThreading(BiTree* T) {//中序线索化二叉树
	if (T == NULL)
		return;
	inOrderThreading(T->lchild);
	if (T->lchild == NULL) {
		T->lchild = pre;
		T->Ltag = THREAD;
	}
	if (pre != NULL && pre->rchild == NULL) {
		pre->rchild = T;
		pre->Rtag = THREAD;
	}
	pre = T;
	inOrderThreading(T->rchild);
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
	inOrderThreading(T);
	char target;
	cin >> target;
	inOrderTraverse(T);
	found(T, target);
	return 0;
}