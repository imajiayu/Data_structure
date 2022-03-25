#include<iostream>
using namespace std;

int a[1000000] = {};
int cnt = 0;

int remove(int target) {
	for (int i = 0; i < cnt; i++)//需要删除的数 设为-1
		if (a[i] == target)
			a[i] = -1;

	int removeNum=0;//与去重相同的出表方法
	for (int i = 0; i < cnt; i++) {
		if (a[i] == -1) {
			removeNum++;
			continue;
		}
		if (removeNum == 0)
			continue;
		a[i - removeNum] = a[i];
	}
	cnt -= removeNum;
	return removeNum;
}

int main() {
	cin >> cnt;
	for (int i = 0; i < cnt; i++)//输入数据
		cin >> a[i];
	int cmd = 0;
	cin >> cmd;
	for (int i = 0; i < cmd; i++) {//输入要删除的数
		int target;
		cin >> target;
		cout << remove(target) << endl;
	}
	for (int i = 0; i < cnt; i++)//输出剩余的数
		cout << a[i] << ' ';
	return 0;
}

