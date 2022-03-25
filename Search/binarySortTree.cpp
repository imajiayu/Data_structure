#include <iostream>
using namespace std;

class Node {//二叉树节点，存储数据与出现次数
public:
	int data;
	int cnt;
public:
	Node();
};

Node::Node() {
	data = 0;
	cnt = 0;
}

class BiTree {//二叉树的存储类型
public:
	Node node;
	BiTree* lchild;
	BiTree* rchild;
public:
	BiTree();
};

BiTree::BiTree() {
	lchild = NULL;
	rchild = NULL;
}


void insert(BiTree* &T, int insertData) {//插入节点
	if (!T) {//若节点不存在，则申请节点
		T = (BiTree*)malloc(sizeof(BiTree));
		T->lchild = T->rchild = NULL;
		T->node.data = insertData;
		T->node.cnt = 1;
		return;
	}
	if (T->node.data == insertData) {//已经存在，cnt++
		T->node.cnt++;
		return;
	}
	else if (T->node.data > insertData)//递归找到插入位置
		insert(T->lchild, insertData);
	else
		insert(T->rchild, insertData);
}

bool deLete(BiTree*& T, int deleteData) {//删除节点
	if (!T)
		return false;
	if (T->node.data == deleteData && T->node.cnt > 1) {//大于1时，cnt--
		T->node.cnt--;
		return true;
	}
	else if (T->node.data == deleteData && T->node.cnt == 1) {//左右子树有一个为空的情况
		if (!T->lchild) {
			BiTree* q = T;
			T = T->rchild;
			free(q);
		}
		else if (!T->rchild) {
			BiTree* q = T;
			T = T->lchild;
			free(q);
		}
		else {//左右子树均不空的情况
			BiTree* q = T;
			BiTree* s = T->lchild;
			while (s->rchild) {
				q = s;
				s = s->rchild;
			}
			T->node.data = s->node.data;
			T->node.cnt = s->node.cnt;
			if (q != T)
				q->rchild = s->lchild;
			else q->lchild = s->lchild;
			delete s;
		}
		return true;
	}
	else if (T->node.data > deleteData)//递归寻找删除位置
		return deLete(T->lchild, deleteData);
	else if (T->node.data < deleteData)
		return deLete(T->rchild, deleteData);
}

int search(BiTree* T, int targetData) {//递归寻找
	if (!T)
		return 0;
	if (T->node.data == targetData)
		return T->node.cnt;
	else if (T->node.data > targetData)
		return search(T->lchild, targetData);
	else return search(T->rchild, targetData);
}

int CNT = 0;
void inOrderTraverse(int* result,BiTree* T) {//中序遍历寻找前缀
	if (T) {
		inOrderTraverse(result,T->lchild);
		result[CNT++] = T->node.data;
		inOrderTraverse(result,T->rchild);
	}
}

int main() {
	BiTree* T = NULL;
	int opNum;
	cin >> opNum;
	for (int i = 0; i < opNum; i++) {
		int op;
		cin >> op;
		if (op == 1) {
			int insertData;
			cin >> insertData;
			insert(T, insertData);
		}
		else if (op == 2) {
			int deleteData;
			cin >> deleteData;
			if (!deLete(T, deleteData))
				cout << "None" << endl;
		}
		else if (op == 3) {
			int targetData;
			cin >> targetData;
			cout << search(T, targetData) << endl;
		}
		else if (op == 4) {
			BiTree* q = T;
			while (q->lchild){
				q = q->lchild;
			}
			cout << q->node.data << endl;
		}
		else {
			int targetData;
			cin >> targetData;
			int result[100000];
			inOrderTraverse(result, T);
			for (int j = -1; j < CNT - 1; j++) {
				if (targetData <= result[j + 1]) {
					if (j == -1) {
						cout << "None" << endl;
						break;
					}
					else {
						cout << result[j] << endl;
						break;
					}
				}
				if (j == CNT - 2)
					cout << result[j + 1] << endl;
			}
			CNT = 0;
		}
	}
	return 0;
}