#include <iostream>
#define MAX_NODE_NUM 9999
#define MAX_NUM 2147483647
using namespace std;

int matrix[MAX_NODE_NUM][MAX_NODE_NUM];
bool P[MAX_NODE_NUM][MAX_NODE_NUM];
bool Final[MAX_NODE_NUM];
int D[MAX_NODE_NUM];

void inputMatrix(int nodeNum, int arcNum) {
	for (int i = 1; i <= nodeNum; i++)
		for (int j = 1; j <= nodeNum; j++)
			matrix[i][j] = MAX_NUM;
	for (int i = 0; i < arcNum; i++) {
		int ui, vi, wi;
		cin >> ui >> vi >> wi;
		matrix[ui][vi] = wi;
		matrix[vi][ui] = wi;
	}
}

void ShortestPath(int nodeNum, int v0) {
	for (int v = 1; v <= nodeNum; v++) {
		Final[v] = false;
		D[v] = matrix[v0][v];
		for (int w = 1; w < nodeNum; w++)
			P[v][w] = false;
		if (D[v] < MAX_NUM) {
			P[v][v0] = true;
			P[v][v] = true;
		}
	}
	D[v0] = 0;
	Final[v0] = true;
	for(int i=1;i<nodeNum;i++){
		int v=-1;
		int min = MAX_NUM;
		for (int w = 1; w <= nodeNum; w++) 
			if(!Final[w])
				if (D[w] < min) {
					v = w;
					min = D[w];
				}
		if (v == -1)
			continue;
		Final[v] = true;
		for (int w = 1; w <= nodeNum; w++) 
			if (!Final[w] && (min + matrix[v][w]) < D[w]&& (min + matrix[v][w]>0)) {
				D[w] = min + matrix[v][w];
				for (int i = 1; i <= nodeNum; i++)
					P[w][i] = P[v][i];
				P[w][w] = true;
			}
	}
}

int main() {
	int n, m, s;
	
	cin >> n >> m >> s;
	inputMatrix(n, m);
	ShortestPath(n, s);
	for (int i = 1; i <= n; i++)
		cout << D[i]<<' ';
}