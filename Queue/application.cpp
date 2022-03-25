#include <iostream>
#include <queue>
using namespace std;

const int dx[4] = { -1,0,1,0 };//四个方位
const int dy[4] = { 0,1,0,-1 };
int matrix[500][500] = { 0 };//原始矩阵
int row, column;//行列数
int num = 0;//细胞总数

class location {//存放坐标的类
public:
	int x;
	int y;
public:
	location(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

void inputMatrix() {//矩阵的输入
	cin >> row >> column;
	for (int i = 1; i <= row; i++)
		for (int j = 1; j <= column; j++)
			cin >> matrix[i][j];
}

bool isOnBoard(int x, int y) {//x，y处的细胞是否在边界上
	if (x == 1 || x == row || y == 1 || y == column)
		return true;
	else return false;
}

bool isCellInMatrix(int x, int y) {//x，y处是否是矩阵内的细胞
	if ((x > 0) && (x <= row) && (y > 0) && (y <= column) && (matrix[x][y]))
		return true;
	else return false;
}

void singleCellSearch(int x, int y) {
	int boardCellNum = 0;//该细胞在边界上所占的数目
	int totalCellNum = 0;//该细胞总的所占的数目
	queue<location> Q;//存放坐标的队列
	num++;//细胞数目++
	if (isOnBoard(x, y))//若在边界，边界数目++
		boardCellNum++;
	totalCellNum++;//总数目++
	matrix[x][y] = 0;//已搜索到的点置零
	Q.push(location(x, y));//该位置入栈
	do {//对四个方向进行搜索，若为细胞，则将其位置入队，然后将已经搜索过周围的坐标出队
		int newX, newY;
		for (int i = 0; i < 4; i++) {
			newX = Q.front().x + dx[i];
			newY = Q.front().y + dy[i];
			if (isCellInMatrix(newX, newY)) {
				if (isOnBoard(newX, newY))////若在边界，边界数目++
					boardCellNum++;
				totalCellNum++;//总数目++
				Q.push(location(newX, newY));
				matrix[newX][newY] = 0;
			}
		}
		Q.pop();
	} while (!Q.empty());//队空时停止搜索
	if (boardCellNum == totalCellNum)//如果边界数目等于总数目，则说明所有细胞均在边界上，num--；
		num--;
}

void cellNumber() {//遍历矩阵，对遇到的第一个细胞进行搜索
	for (int i = 1; i <= row; i++)
		for (int j = 1; j <= column; j++)
			if (matrix[i][j])
				singleCellSearch(i, j);
}

int main() {
	inputMatrix();
	cellNumber();
	cout << num;
}


