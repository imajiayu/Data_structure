#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
using namespace std;
clock_t start, finish;


int Min(int* temp, int i, int len) {
	int min= 2147334140;
	int result;
	for (int j = i; j <= len; j++)
		if (temp[j] < min) {
			result = j;
			min = temp[j];
		}
	return result;
}

void SelectSort() {//选择排序
	int len=10000;
	int* temp = (int*)malloc((len + 1) * sizeof(int));
	ifstream in("E:\\数据结构\\Sort\\Inverse10K.txt");
	for (int i = 1; i <= len; i++)
		in >> temp[i];
	start = clock();
	for (int i = 1; i < len; i++) {
		int j = Min(temp, i, len);
		if (i != j) {
			int t = temp[i];
			temp[i] = temp[j];
			temp[j] = t;
		}
	}
	finish = clock();
}


int main() {
	SelectSort();
	cout << double(finish - start) / CLOCKS_PER_SEC<<"s";
}