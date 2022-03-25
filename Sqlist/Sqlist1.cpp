#include <iostream>
#include <string.h>
#define LIST_INIT_SIZE 10000
#define LIST_INCREMENT 1000
using namespace std;

//学生类 
class Student {
public:
	char ID[20]; //学号
	char name[20]; //姓名
public:
	Student(); //初始化
	void init(); //对学生信息进行输入
};

Student::Student() {
	ID[0] = '\0';
	name[0] = '\0';
}

void Student::init() {
	cin >> this->ID >> this->name;
}

//顺序表类
class Sqlist {
public:
	Student* elem;
	int length;
	int listSize;
public:
	Sqlist();
	bool insert(int i, Student stu);
	bool remove(int i);
	int checkName(char name[]);
	int checkNo(char[]);
};
//初始化构造函数
Sqlist::Sqlist() {
	this->elem = (Student*)malloc(LIST_INIT_SIZE * sizeof(Student));;
	this->length = 0;
	this->listSize = LIST_INIT_SIZE;
}

bool Sqlist::insert(int i,Student stu) {
	if (i<1 || i>this->length + 1)
		return false;
	if (this->length >= this->listSize) {
		Student* newbase = (Student*)realloc(this->elem, (this->listSize + LIST_INCREMENT) * sizeof(Student));
		if (!newbase)
			return false;
		this->elem = newbase;
		this->listSize += LIST_INCREMENT;
	}
	Student* q = &(this->elem[i - 1]);
	if (this->length >0) { //这里要判断长度是否为0，否则会出现访问越界
		for (Student* p = &(this->elem[this->length - 1]); p >= q; --p)
			*(p + 1) = *p;
		*q = stu;
	}
	else *q=stu; //如果长度为0，则直接赋值
	this->length++;
	return true;
}

bool Sqlist::remove(int i) {
	if (i<1 || i>this->length)
		return false;
	Student* p = &(this->elem[i - 1]);
	p++;
	if (this->length > 0) //判断长度是否为0，否则会出现访问越界
		for (Student* q = this->elem + this->length - 1; p <= q; ++p)
			*(p - 1) = *p;
	else return false;
	this->length--;
	return true;
}

int Sqlist::checkName(char name[]) {
	for (int i = 0; i < this->length; i++)
		if (!strcmp(name,this->elem[i].name))
			return i + 1;
	return -1;
}

int Sqlist::checkNo(char id[]) {
	for (int i = 0; i < this->length; i++)
		if (!strcmp(id, this->elem[i].ID))
			return i + 1;
	return -1;
}

int main() {
	Sqlist L;
	int num;
	cin >> num;
	for (int i = 0; i < num; i++) {
		Student temp;
		temp.init();
		L.insert(i+1,temp);
	}
	//循环指令
	while (true) {
		char cmd[20];
		cin >> cmd;
		if (!strcmp(cmd, "insert")) {
			int i;
			Student stu;
			cin >> i;
			stu.init();
			if (L.insert(i, stu))
				cout << 0 << endl;
			else cout << -1 << endl;
		}
		if (!strcmp(cmd, "remove")) {
			int i;
			cin >> i;
			if (L.remove(i))
				cout << 0 << endl;
			else cout << -1 << endl;
			
		}
		if (!strcmp(cmd, "check")) {
			char cmd2[20];
			cin >> cmd2;
			if (!strcmp(cmd2, "name")) {
				char name[20];
				cin >> name;
				int t = L.checkName(name);
				if (t != -1)
					cout << t << ' ' << L.elem[t - 1].ID << ' ' << L.elem[t - 1].name << endl;
				else cout << -1 << endl;
			}
			if (!strcmp(cmd2, "no")) {
				char id[20];
				cin >> id;
				int t = L.checkNo(id);
				if(t!=-1)
					cout << t <<' '<<L.elem[t - 1].ID <<' '<< L.elem[t - 1].name << endl;
				else cout << -1 << endl;
			}
		}
		if (!strcmp(cmd, "end")) {
			cout << L.length;
			return 0;
		}
	}
}
