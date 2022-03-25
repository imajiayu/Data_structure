#include <iostream>
#include <stack>
using namespace std;

const int matrix[5][5] = {
	{0,1,1,0,1},
	{1,0,1,0,1},
	{1,1,0,1,1},
	{0,0,1,0,1},
	{1,1,1,1,0}
};//�ڽӾ���

int visited[5][5] = {
	{ 0,0,0,0,0 },
	{ 0,0,0,0,0 },
	{ 0,0,0,0,0 },
	{ 0,0,0,0,0 },
	{ 0,0,0,0,0 },
};//��¼�ڵ��Ƿ���ʹ�

int order[10];//����˳��
int cnt = 0;//���ܵ�·����

void printResult() {//��ӡ����·��
	cout << order[0]+1;
	for (int i = 1; i < 8; i++)
		cout << "->" << order[i] + 1;
	cout << endl;
}

void dfs(int nowNode, int depth) {//dfs�������ܵ�·��
	for (int i = 0; i < 5; i++) {
		if (matrix[nowNode][i] && !visited[nowNode][i]) {
			order[depth] = i;
			visited[nowNode][i] = 1;
			visited[i][nowNode] = 1;
			if (depth == 8) {//����Ϊ����ʱ��˵��ȫ������
				printResult();
				cnt++;
			}
			else
				dfs(i, depth + 1);
			visited[nowNode][i] = 0;
			visited[i][nowNode] = 0;//��ԭ
		}
	}
}

void oneStrokeDrawing() {//��ÿ���ڵ�dfs
	for (int i = 0; i < 5; i++) {
		order[0] = i;
		dfs(i, 1);
	}
	cout << "����·���������ǣ�" << cnt;
}



int main() {
	oneStrokeDrawing();
}