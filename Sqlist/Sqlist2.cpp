#include<iostream>
using namespace std;
int a[1000000] = {};

int main() {
    int cnt = 0;
    cin>>cnt;
    for (int i = 0; i < cnt; i++){ //输入数据
        cin >> a[i];
    }
    for (int i = 0; i < cnt; i++){ //去重
        if (a[i] == -1)
            continue;
        int t = a[i];
        for (int j = i + 1; j < cnt; j++){
            if (a[j] == t) {
                a[j] = -1;//将需要删除的数据替换为-1
            } 
        }
    }

    int remove = 0; //每个-1后面的数据需要向前移动的位数
    for (int i = 0; i < cnt; i++){
        if (a[i] == -1) { 
            remove++;
            continue;
        }
        if (remove == 0)
            continue; 
        a[i - remove] = a[i];//遇到需要移动的数据时 向前移动remove位
    }
    cnt -= remove; //改变顺序表长度
    for (int i = 0; i < cnt; i++)
        cout << a[i] << ' ';
    return 0;
}
  