#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <string>
using namespace std;

typedef struct {
	int wight;
	int parent;
	int lChild;
	int rchild;
}HTNode, * HuffmanTree;

typedef char** HuffmanCode;

HuffmanTree HT = NULL;
HuffmanCode HC;
int w[128];

void select(HuffmanTree HT, int n, int& s1, int& s2) {//找出现有树中权值最小的两棵树
	int least = 9999;
	int preleast = 9999;
	int p = 0;
	int q = 0;
	for (int i = 1; i <= n; i++)
		if (HT[i].parent == 0) {
			if (HT[i].wight <= least) {
				preleast = least;
				q = p;
				least = HT[i].wight;
				p = i;
			}
			else if (HT[i].wight > least&& HT[i].wight <= preleast) {

				preleast = HT[i].wight;
				q = i;
			}
		}
	s1 = p;
	s2 = q;
}

void HuffmanCoding(HuffmanTree& HT, HuffmanCode& HC, int w[], int n) {//生成赫夫曼编码
	if (n <= 1)
		return;
	int m = 2 * n - 1;
	int i = 0;
	HuffmanTree p = NULL;
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));
	for (p = HT; i <= n; ++i, ++p)
		*p = { w[i],0,0,0 };
	for (; i <= m; ++i, ++p)
		*p = { 0,0,0,0 };
	for (int i = n + 1; i <= m; i++) {
		int s1, s2;
		select(HT, i - 1, s1, s2);
		HT[s1].parent = HT[s2].parent = i;
		HT[i].lChild = s1;
		HT[i].rchild = s2;
		HT[i].wight = HT[s1].wight + HT[s2].wight;
	}
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));
	char* cd = (char*)malloc(n * sizeof(char));
	cd[n - 1] = '\0';
	for (int i = 1; i <= n; i++) {
		int start = n - 1;
		for (int c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent) {
			if (HT[f].lChild == c)
				cd[--start] = '0';
			else cd[--start] = '1';
			HC[i] = (char*)malloc((n - start) * sizeof(char));
			strcpy(HC[i], &cd[start]);
		}
	}
}

int main() {
	map<char, string> codeMap;//用map来存储，key值为字符，value值为对应的编码字符串
	for (int i = 0; i <= 127; i++)
		w[i] = i;
	HuffmanCoding(HT, HC, w, 127);
	for (int i = 1; i <= 127; i++) {
		char c = i;
		cout << c << "'s HuffmanCode is:" << HC[i] << endl;
		codeMap.insert(pair<char, string>(c, HC[i]));
	}
	cout << "请输入你想要转换为二进制编码的文本：" << endl;
	char S[100000];
	cin >> S;
	for (int i = 0;; i++) {
		if (S[i] == '\0')
			break;
		cout << codeMap.at(S[i]);
	}
	cout << endl;
	cout << "请输入你想要转换为文本的二进制编码：" << endl;
	cin >> S;
	int temp = 253;//从根节点开始搜索，输入的字符为0则向左走，反之向右走，一直走到叶子结点，就找到了对应字符串
	for (int i = 0;; i++) {
		if (S[i] == '\0')
			break;

		if (S[i] == '0')
			temp = HT[temp].lChild;
		else temp = HT[temp].rchild;

		if (HT[temp].lChild == 0 && HT[temp].rchild == 0) {
			char c = temp;
			cout << c;
			temp = 253;
		}
	}
}