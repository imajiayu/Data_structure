#include <iostream>
#include <stack>
using namespace std;

class Node {//��ڵ�
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

class HeadNode {//ͷ���
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

HeadNode* inputGraph(int nodeNum, int arcNum) {//����ͼ
	HeadNode* headNode = (HeadNode*)malloc(nodeNum * sizeof(HeadNode));//�ڽӱ��׸�ͷ���
	for (int i = 0; i < nodeNum; i++) {//����ڵ�
		headNode[i].data = i+1;
		headNode[i].inDegree = 0;
		headNode[i].firstarc = NULL;
	}
	for (int i = 0; i < arcNum; i++) {//����߻�
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

bool topologicalSort(HeadNode* G, int nodeNum) {//��������
	stack<int> S;
	int cnt = 0;
	for (int i = 0; i < nodeNum; i++)//���Ϊ��Ľڵ���ջ
		if (G[i].inDegree == 0)
			S.push(i);
	while (!S.empty()){
		int node = S.top();
		S.pop();
		cnt++;
		for (Node* p = G[node].firstarc; p; p = p->nextarc) {
			if (!(--G[p->adjvec].inDegree))//����һ�����Ϊ0����ջ
				S.push(p->adjvec);
		}
	}
	if (cnt == nodeNum)//����ڵ��������ܽ������˵���������������޻�
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