#define LINK 0
#define THREAD 1;
#include <iostream>
#include <queue>
using namespace std;

class BiTree {//�����������洢�ṹ
public:
	char data;//������
	int Ltag;
	int Rtag;
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

BiTree* preCreate() {//����ݹ齨��������
	BiTree* T;
	char elem;
	cin >> elem;
	if (elem == '#')//�ڵ�Ϊ��
		T = NULL;
	else {
		T = (BiTree*)malloc(sizeof(BiTree));
		T->data = elem;
		T->lchild = preCreate();//�ݹ齨��������
		T->rchild = preCreate();//�ݹ齨��������
	}
	return T;
}

BiTree* first(BiTree* T) {//��������������������ĵ�һ���ڵ���һֱ�ߵ�����˵Ľڵ�
	BiTree* p=T;
	if (p == NULL)
		return NULL;
	while (p->Ltag == LINK)
		p = p->lchild;
	return p;
}

BiTree* next(BiTree* T) {//���������������������һ���ڵ����������ĵ�һ���ڵ���̽ڵ�
	BiTree* p=T;
	if (p->Rtag == 0)
		return first(p->rchild);
	else return p->rchild;
}

void inOrderTraverse(BiTree* T) {//��������Ѿ������������Ķ�����
	for (BiTree* p = first(T); p != NULL; p = next(p)) 
		cout << p->data;
	cout << endl;
}

void found(BiTree* T, char target) {//������������������������preָ���¼ǰ���ڵ�
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

void inOrderThreading(BiTree* T) {//����������������
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

void setZero(BiTree* T) {//��־λ��0
	if (T) {
		T->Ltag = T->Rtag = 0;
		setZero(T->lchild);
		setZero(T->rchild);
	}
}

void setLRtag(BiTree* T) {//��־λ��Ӧ���õ���
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