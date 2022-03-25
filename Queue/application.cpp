#include <iostream>
#include <queue>
using namespace std;

const int dx[4] = { -1,0,1,0 };//�ĸ���λ
const int dy[4] = { 0,1,0,-1 };
int matrix[500][500] = { 0 };//ԭʼ����
int row, column;//������
int num = 0;//ϸ������

class location {//����������
public:
	int x;
	int y;
public:
	location(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

void inputMatrix() {//���������
	cin >> row >> column;
	for (int i = 1; i <= row; i++)
		for (int j = 1; j <= column; j++)
			cin >> matrix[i][j];
}

bool isOnBoard(int x, int y) {//x��y����ϸ���Ƿ��ڱ߽���
	if (x == 1 || x == row || y == 1 || y == column)
		return true;
	else return false;
}

bool isCellInMatrix(int x, int y) {//x��y���Ƿ��Ǿ����ڵ�ϸ��
	if ((x > 0) && (x <= row) && (y > 0) && (y <= column) && (matrix[x][y]))
		return true;
	else return false;
}

void singleCellSearch(int x, int y) {
	int boardCellNum = 0;//��ϸ���ڱ߽�����ռ����Ŀ
	int totalCellNum = 0;//��ϸ���ܵ���ռ����Ŀ
	queue<location> Q;//�������Ķ���
	num++;//ϸ����Ŀ++
	if (isOnBoard(x, y))//���ڱ߽磬�߽���Ŀ++
		boardCellNum++;
	totalCellNum++;//����Ŀ++
	matrix[x][y] = 0;//���������ĵ�����
	Q.push(location(x, y));//��λ����ջ
	do {//���ĸ����������������Ϊϸ��������λ����ӣ�Ȼ���Ѿ���������Χ���������
		int newX, newY;
		for (int i = 0; i < 4; i++) {
			newX = Q.front().x + dx[i];
			newY = Q.front().y + dy[i];
			if (isCellInMatrix(newX, newY)) {
				if (isOnBoard(newX, newY))////���ڱ߽磬�߽���Ŀ++
					boardCellNum++;
				totalCellNum++;//����Ŀ++
				Q.push(location(newX, newY));
				matrix[newX][newY] = 0;
			}
		}
		Q.pop();
	} while (!Q.empty());//�ӿ�ʱֹͣ����
	if (boardCellNum == totalCellNum)//����߽���Ŀ��������Ŀ����˵������ϸ�����ڱ߽��ϣ�num--��
		num--;
}

void cellNumber() {//�������󣬶������ĵ�һ��ϸ����������
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


