#include <iostream>
using namespace std;

class Node {//��ڵ�
public:
	int adjvec;
	Node* nextarc;
	int info;
public:
	Node();
};

Node::Node(){
	adjvec = -1;
	info = 0;
	nextarc = NULL;
}

class HeadNode {//ͷ���
public:
	char data;
	Node* firstarc;
public:
	HeadNode();
};

HeadNode::HeadNode() {
	data = '\0';
	firstarc = NULL;
}

bool graph(bool isWeighted, bool isDirected,int nodeNum, int arcNum) {//����ͼ�������ֱ�Ϊ ����Ȩֵ �Ƿ����� �ڵ������ߵĸ���
	int matrix[100][100] = { 0 };//�ڽӾ���
	HeadNode* headNode = (HeadNode*)malloc(nodeNum * sizeof(HeadNode));//�ڽӱ��׸�ͷ���
	for (int i = 0; i < nodeNum; i++) {//����ڵ�
		cin >> headNode[i].data;
		headNode[i].firstarc = NULL;
	}
	for (int i = 0; i < arcNum; i++) {//����߻�
		char start, end;
		int p, q, weight;
		if (!isWeighted) {
			cin >> start >> end;
			for (p = 0; p < nodeNum; p++)//��λ�ߵ������ڵ���±�
				if (headNode[p].data == start)
					break;
			for (q = 0; q < nodeNum; q++)
				if (headNode[q].data == end)
					break;
			matrix[p][q] = 1;//���ڽӾ���ֵ
			Node* newNode = (Node*)malloc(sizeof(Node));//ͷ�巨�޸��ڽӱ�
			newNode->adjvec = q;
			newNode->nextarc = headNode[p].firstarc;
			headNode[p].firstarc = newNode;
			if (!isDirected) {
				matrix[q][p] = 1;
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->adjvec = p;
				newNode->nextarc = headNode[q].firstarc;
				headNode[q].firstarc = newNode;
			}
		}
		else {
			cin >> start >> end >> weight;
			for (p = 0; p < nodeNum; p++)
				if (headNode[p].data == start)
					break;
			for (q = 0; q < nodeNum; q++)
				if (headNode[q].data == end)
					break;
			matrix[p][q] = weight;
			Node* newNode = (Node*)malloc(sizeof(Node));
			newNode->adjvec = q;
			newNode->info = weight;
			newNode->nextarc = headNode[p].firstarc;
			headNode[p].firstarc = newNode;
			if (!isDirected) {
				matrix[q][p] = weight;
				Node* newNode = (Node*)malloc(sizeof(Node));
				newNode->adjvec = p;
				newNode->info = weight;
				newNode->nextarc = headNode[q].firstarc;
				headNode[q].firstarc = newNode;
			}
		}
	}
	for (int i = 0; i < nodeNum; i++)//���
		cout << headNode[i].data << ' ';
	cout << endl;
	for (int i = 0; i < nodeNum; i++) {
		for (int j = 0; j < nodeNum; j++) {
			cout << "   " << matrix[i][j];
		}
			cout << endl;
	}
	if (!isWeighted) {
		for (int i = 0; i < nodeNum; i++) {
			cout << headNode[i].data << "-->";
			for (Node* p = headNode[i].firstarc; p; p = p->nextarc) {
				cout << p->adjvec << ' ';
			}
			cout << endl;
		}
	}
	else {
		for (int i = 0; i < nodeNum; i++) {
			cout << headNode[i].data << "-->";
			for (Node* p = headNode[i].firstarc; p; p = p->nextarc) {
				cout << p->adjvec << ',' << p->info << ' ';
			}
			cout << endl;
		}
	}
	return true;
}

int main() {
	int type;
	int n, m;
	cin >> type;
	cin >> n >> m;
	switch (type){
	case 1:graph(false, true, n, m); break;
	case 2:graph(true, true, n, m); break;
	case 3:graph(false, false, n, m); break;
	case 4:graph(true, false, n, m); break;
	default:
		break;
	}
}