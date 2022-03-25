#include <iostream>
#define MAX_NODE_NUM 500
using namespace std;

int matrix[MAX_NODE_NUM][MAX_NODE_NUM];//邻接矩阵
//辅助数组
typedef struct Closedge {
	int adjvex;
	int lowcost;
};

Closedge closedge[MAX_NODE_NUM];

void inputMatrix(int nodeNum) {
	for (int i = 0; i < nodeNum; i++)
		for (int j = 0; j < nodeNum; j++)
			cin >> matrix[i][j];
}

int MiniSpanTree(int nodeNun, int startNode) {
	int sum = 0;
	int k = startNode;
	//辅助数组初始化
	for (int i = 0; i < nodeNun; i++)
		if (i != k)
			closedge[i] = { k,matrix[k][i] };
	closedge[k].lowcost = 0;
	for (int i = 0; i < nodeNun; i++) {
		int lowest=1000;
		for(int j=0;j<nodeNun;j++)
			if (closedge[j].lowcost > 0 && closedge[j].lowcost <= lowest) {
				lowest = closedge[j].lowcost;
				k = j;
			}
		sum += closedge[k].lowcost;
		closedge[k].lowcost = 0;
		for (int j = 0; j < nodeNun; j++)
			if (matrix[k][j] < closedge[j].lowcost)
				closedge[j] = { k,matrix[k][j] };
	}
	return sum;
}

int main() {
	int nodeNum;
	cin >> nodeNum;
	inputMatrix(nodeNum);
	cout << MiniSpanTree(nodeNum, 0);
}



