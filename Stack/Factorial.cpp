#define _CRT_SECURE_NO_WARNINGS
#include <stack>
#include <iostream>
using namespace std;

class Data {//数据类，包括输入参数与返回地址
public:
	int n;//输入参数
	int* returnAddress;
public:
	Data() {//构造器
		n = 0;
		returnAddress = (int*)malloc(sizeof(int));
	}
	void setter(int n) {//设定的值n的值
		this->n = n;
	}
};

int factorial(int n) {//利用栈模拟递归求阶乘
	if (n == 0)//0的阶乘为1；
		return 1;
	stack<Data> mystack;//栈
	Data data;//存储最终结果的数据类
	data.setter(n);//初始化
	while (data.n != 1) {//n=1？
		mystack.push(data);//开始递归
		data.setter(data.n - 1);//入栈
	}
	while (!mystack.empty()) {//栈空？
		if (mystack.top().n == 1) {//当n=1时，return1
			data.n = 1;
			mystack.pop();
		}
		else {
			data.n *= mystack.top().n;//回溯
			mystack.pop();
		}
	}
	return data.n;//end
}

int main() {
	cout << "Please enter the factorial you want:" << endl;
	int n;
	cin >> n;
	cout << "The result is:" << factorial(n);
	return 0;
}