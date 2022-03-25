#include <iostream>
#define null -1
#define MAX_NODE_NUM 10
using namespace std;

class BiTreeNode {//序列化二叉树类
public:
	char data;
	int lchild;
	int rchild;
};

int createTree(BiTreeNode T[]) {//根据输入建立一个二叉树，返回其根节点
	int root;
	char lc, rc;
	int searchRoot[MAX_NODE_NUM] = { 0 };
	int N;
	cin >> N;
	if (N == 0)
		return null;
	for (int i = 0; i < N; i++) {
		cin >> T[i].data >> lc >> rc;

		if (lc != '-') {
			T[i].lchild = lc - '0';
			searchRoot[T[i].lchild] = 1;
		}
		else T[i].lchild = null;

		if (rc != '-') {
			T[i].rchild = rc - '0';
			searchRoot[T[i].rchild] = 1;
		}
		else T[i].rchild = null;//节点为空
	}

	for(int i=0;i<N;i++)//当一个节点既不是某个节点的左节点，也不是某个节点的右节点时，其为根节点
		if (searchRoot[i] == 0) {
			root = i;
			break;
		}
	return root;
}

bool isomorphic(BiTreeNode T1[], int root1, BiTreeNode T2[], int root2) {//递归判断是否同构
	if (root1 == -1 && root2 == -1)
		return true;
	if ((root1 != -1 && root2 == -1) || (root1 == -1 && root2 != -1))
		return false;
	if (T1[root1].data != T2[root2].data)
		return false;
	else {
		if (isomorphic(T1, T1[root1].lchild, T2, T2[root2].lchild) && isomorphic(T1, T1[root1].rchild, T2, T2[root2].rchild))//左右子树交换前是否相同
			return true;
		else if (isomorphic(T1, T1[root1].lchild, T2, T2[root2].rchild) && isomorphic(T1, T1[root1].rchild, T2, T2[root2].lchild))//左右子树交换后是否相同
			return true;
		else return false;
	}
}

int BiTreeDepth(BiTreeNode T[], int root) {//递归搜索树的深度
	int depthl,depthr;
	if (root != -1) {
		depthl = BiTreeDepth(T, T[root].lchild);
		depthr = BiTreeDepth(T, T[root].rchild);
		if (depthl >= depthr)
			return (depthl + 1);
		else return (depthr + 1);
	}
	else return 0;
}

int main() {
	BiTreeNode T1[MAX_NODE_NUM];
	BiTreeNode T2[MAX_NODE_NUM];
	int root1 = createTree(T1);
	int root2 = createTree(T2);
	if (isomorphic(T1, root1, T2, root2))
		cout << "Yes" << endl;
	else cout << "No" << endl;
	cout << BiTreeDepth(T1, root1) << endl;
	cout << BiTreeDepth(T2, root2) << endl;
	return 0;
}