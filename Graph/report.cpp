#include <iostream>
#include <stack>
using namespace std;

const int matrix[5][5] = {
	{0,1,1,0,1},
	{1,0,1,0,1},
	{1,1,0,1,1},
	{0,0,1,0,1},
	{1,1,1,1,0}
};//邻接矩阵

int visited[5][5] = {
	{ 0,0,0,0,0 },
	{ 0,0,0,0,0 },
	{ 0,0,0,0,0 },
	{ 0,0,0,0,0 },
	{ 0,0,0,0,0 },
};//记录节点是否访问过

int order[10];//访问顺序
int cnt = 0;//可能的路径数

void printResult() {//打印单条路径
	cout << order[0]+1;
	for (int i = 1; i < 8; i++)
		cout << "->" << order[i] + 1;
	cout << endl;
}

void dfs(int nowNode, int depth) {//dfs搜索可能的路径
	for (int i = 0; i < 5; i++) {
		if (matrix[nowNode][i] && !visited[nowNode][i]) {
			order[depth] = i;
			visited[nowNode][i] = 1;
			visited[i][nowNode] = 1;
			if (depth == 8) {//层数为边数时，说明全部遍历
				printResult();
				cnt++;
			}
			else
				dfs(i, depth + 1);
			visited[nowNode][i] = 0;
			visited[i][nowNode] = 0;//还原
		}
	}
}

void oneStrokeDrawing() {//对每个节点dfs
	for (int i = 0; i < 5; i++) {
		order[0] = i;
		dfs(i, 1);
	}
	cout << "可能路径的数量是：" << cnt;
}



int main() {
	oneStrokeDrawing();
}