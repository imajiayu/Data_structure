#include <iostream>
#include <stack>
using namespace std;

class Node {//表节点
public:
	int adjvec;
	Node* nextarc;
	int info;
public:
	Node();
};

Node::Node() {
	adjvec = -1;
	info = 0;
	nextarc = NULL;
}

class HeadNode {//头结点
public:
	int data;
	int inDegree;
	Node* firstarc;
public:
	HeadNode();
};

HeadNode::HeadNode() {
	data = 0;
	inDegree = 0;
	firstarc = NULL;
}

HeadNode* inputGraph(int nodeNum, int arcNum) {//生成图
	HeadNode* headNode = (HeadNode*)malloc(nodeNum * sizeof(HeadNode));//邻接表首个头结点
	for (int i = 0; i < nodeNum; i++) {//输入节点
		headNode[i].data = i+1;
		headNode[i].inDegree = 0;
		headNode[i].firstarc = NULL;
	}
	for (int i = 0; i < arcNum; i++) {//输入边或弧
		int start, end;
		int p, q, weight;
		cin >> start >> end >> weight;
		for (p = 0; p < nodeNum; p++)
			if (headNode[p].data == start)
				break;
		for (q = 0; q < nodeNum; q++)
			if (headNode[q].data == end)
				break;
		headNode[q].inDegree++;
		Node* newNode = (Node*)malloc(sizeof(Node));
		newNode->adjvec = q;
		newNode->info = weight;
		newNode->nextarc = headNode[p].firstarc;
		headNode[p].firstarc = newNode;
	}
	return headNode;
}

bool topologicalSort(HeadNode* G, int nodeNum) {//拓扑排序
	stack<int> S;
	int cnt = 0;
	for (int i = 0; i < nodeNum; i++)//入度为零的节点入栈
		if (G[i].inDegree == 0)
			S.push(i);
	while (!S.empty()){
		int node = S.top();
		S.pop();
		cnt++;
		for (Node* p = G[node].firstarc; p; p = p->nextarc) {
			if (!(--G[p->adjvec].inDegree))//若减一后入度为0，入栈
				S.push(p->adjvec);
		}
	}
	if (cnt == nodeNum)//输出节点数等于总结点数，说明可以拓扑排序，无环
		return true;
	else return false;
}

int main() {
	int n, m;
	cin >> n >> m;
	HeadNode* G=inputGraph(n, m);
	if (topologicalSort(G, n))
		cout << 1;
	else cout << 0;
}