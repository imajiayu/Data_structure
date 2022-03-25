#define MAX_NODE_NUM 20
#include <iostream>
#include <string.h>
#include <queue>
using namespace std;
int matrix[MAX_NODE_NUM][MAX_NODE_NUM];//邻接矩阵

bool inputGraph(int nodeNum, int arcNum) {//给邻接矩阵赋值
	for (int i = 0; i < arcNum; i++) {//输入边
		int p, q;
		cin >> p >> q;
		matrix[p][q] = 1;
		matrix[q][p] = 1;
	}
	return true;
}

void DFS(int* visited, int node, int nodeNum, int depth) {//从单个节点开始进行深度优先搜索
	if (!depth)
		cout << node;
	else cout << ' ' << node;
	visited[node] = 1;
	for (int j = 0; j < nodeNum; j++)
		if (matrix[node][j] == 1 && !visited[j])
			DFS(visited, j, nodeNum, depth + 1);
}

void DFSsearch(int nodeNum) {//对整个矩阵进行深度优先搜索
	int visited[MAX_NODE_NUM] = { 0 };
	for (int i = 0; i < nodeNum; i++)
		if (!visited[i]) {
			cout << '{';
			DFS(visited, i, nodeNum, 0);
			cout << '}';
		}
	cout << endl;
}

void BFS(int* visited, int node, int nodeNum) {//从单个节点开始进行广度优先搜索
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

void BFSsearch(int nodeNum) {//对整个矩阵进行广度优先搜素
	int visited[MAX_NODE_NUM] = { 0 };
	for (int i = 0; i < nodeNum; i++)
		if (!visited[i]) {
			cout << '{';
			BFS(visited, i, nodeNum);
			cout << '}';
		}
}

int main() {
	memset(matrix, 0, sizeof(matrix));//邻接矩阵初始化
	int n, m;
	cin >> n >> m;
	inputGraph(n, m);
	DFSsearch(n);
	BFSsearch(n);
	return 0;
}