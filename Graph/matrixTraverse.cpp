#define MAX_NODE_NUM 20
#include <iostream>
#include <string.h>
#include <queue>
using namespace std;
int matrix[MAX_NODE_NUM][MAX_NODE_NUM];//�ڽӾ���

bool inputGraph(int nodeNum, int arcNum) {//���ڽӾ���ֵ
	for (int i = 0; i < arcNum; i++) {//�����
		int p, q;
		cin >> p >> q;
		matrix[p][q] = 1;
		matrix[q][p] = 1;
	}
	return true;
}

void DFS(int* visited, int node, int nodeNum, int depth) {//�ӵ����ڵ㿪ʼ���������������
	if (!depth)
		cout << node;
	else cout << ' ' << node;
	visited[node] = 1;
	for (int j = 0; j < nodeNum; j++)
		if (matrix[node][j] == 1 && !visited[j])
			DFS(visited, j, nodeNum, depth + 1);
}

void DFSsearch(int nodeNum) {//������������������������
	int visited[MAX_NODE_NUM] = { 0 };
	for (int i = 0; i < nodeNum; i++)
		if (!visited[i]) {
			cout << '{';
			DFS(visited, i, nodeNum, 0);
			cout << '}';
		}
	cout << endl;
}

void BFS(int* visited, int node, int nodeNum) {//�ӵ����ڵ㿪ʼ���й����������
	queue<int> Q;
	cout << node;
	visited[node] = 1;
	Q.push(node);
	while (!Q.empty()) {
		node = Q.front();
		Q.pop();
		for (int j = 0; j < nodeNum; j++)
			if (matrix[node][j] == 1 && !visited[j]) {
				cout << ' ' << j;
				visited[j] = 1;
				Q.push(j);
			}
	}
}

void BFSsearch(int nodeNum) {//������������й����������
	int visited[MAX_NODE_NUM] = { 0 };
	for (int i = 0; i < nodeNum; i++)
		if (!visited[i]) {
			cout << '{';
			BFS(visited, i, nodeNum);
			cout << '}';
		}
}

int main() {
	memset(matrix, 0, sizeof(matrix));//�ڽӾ����ʼ��
	int n, m;
	cin >> n >> m;
	inputGraph(n, m);
	DFSsearch(n);
	BFSsearch(n);
	return 0;
}