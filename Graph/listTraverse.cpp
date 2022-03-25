#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
using namespace std;

class Node {//表节点
public:
	int adjvec;
	Node* nextarc;
public:
	Node();
};

Node::Node() {
	adjvec = -1;
	nextarc = NULL;
}

class HeadNode {//头结点
public:
	int data;
	Node* firstarc;
public:
	HeadNode();
};

HeadNode::HeadNode() {
	data = -1;
	firstarc = NULL;
}

void endInsert(HeadNode* headNode, Node* newNode) {
	Node* p=headNode->firstarc;
	if (p == NULL) {
		headNode->firstarc = newNode;
		newNode->nextarc = NULL;
		return;
	}
	else
		while (p->nextarc != NULL)
			p = p->nextarc;
	p->nextarc = newNode;
	newNode->nextarc = NULL;
}

HeadNode* graph(int nodeNum, int arcNum) {//生成图，参数分别为 有无权值 是否有向 节点个数与边的个数
	HeadNode* headNode = (HeadNode*)malloc(nodeNum * sizeof(HeadNode));//邻接表首个头结点
	for (int i = 0; i < nodeNum; i++) {//输入节点
		headNode[i].data=i;
		headNode[i].firstarc = NULL;
	}
	for (int i = 0; i < arcNum; i++) {//输入边或弧
		int start, end;
		int p, q;
		cin >> start >> end;
		for (p = 0; p < nodeNum; p++)//定位边的两个节点的下标
			if (headNode[p].data == start)
				break;
		for (q = 0; q < nodeNum; q++)
			if (headNode[q].data == end)
				break;
		Node* newNode1 = (Node*)malloc(sizeof(Node));//尾插法修改邻接表
		newNode1->adjvec = q;
		newNode1->nextarc = headNode[p].firstarc;
		headNode[p].firstarc = newNode1;

		Node* newNode2 = (Node*)malloc(sizeof(Node));
		newNode2->adjvec = p;
		newNode2->nextarc = headNode[q].firstarc;
		headNode[q].firstarc = newNode2;
	}
	return headNode;
}

void DFS(int* visited, HeadNode* G, int node,int depth) {
	Node* p;
	if (depth == 0)
		cout << G[node].data;
	else cout << ' ' << G[node].data;
	visited[node] = 1;
	p = G[node].firstarc;
	while (p) {
		if (!visited[p->adjvec])
			DFS(visited, G, p->adjvec,depth+1);
		p = p->nextarc;
	}
}

void DFSTraverse(HeadNode* G, int nodeNum) {
	int visited[100] = {0};
	for (int i = 0; i < nodeNum; i++)
		if (!visited[i]) {
			cout << '{';
			DFS(visited, G, i,0);
			cout << '}';
		}
	cout << endl;
}

void BFS(int* visited, HeadNode* G, int node) {
	Node* p;	
	queue<int> Q;
	cout << G[node].data;
	visited[node] = 1;
	Q.push(node);
	while (!Q.empty()){
		node = Q.front();
		Q.pop();
		p = G[node].firstarc;
		while (p){
			if (!visited[p->adjvec])
			{
				cout <<' '<< G[p->adjvec].data;
				visited[p->adjvec] = 1;
				Q.push(p->adjvec);
			}
			p = p->nextarc;
		}
	}
}

void BFSTraverse(HeadNode* G, int nodeNum) {
	int visited[100] = { 0 };
	for (int i = 0; i < nodeNum; i++)
		if (!visited[i]) {
			cout << '{';
			BFS(visited, G, i);
			cout << '}';
		}
}


int main() {
	int n, m;
	cin >> n >> m;
	HeadNode* G=graph(n, m);
	DFSTraverse(G, n);
	BFSTraverse(G, n);
}