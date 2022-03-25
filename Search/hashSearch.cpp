#include <iostream>
#include <math.h>
#include <string.h>
using namespace std;

bool is_prime_number(int n) {//判断是否为素数
    for (int i = 2; i <= sqrt(n); i++) {
        if (!(n % i))
            return false;
    }
    return true;
}

int generate_hash(char name[],int P) {//hash函数
    int temp = 0;
    for (int i = 0; i < strlen(name); i++)
        temp = (temp * 37 + name[i]) % P;

    return temp;
}

int hashLocation(int* hashList , int value, int P) {//寻找插入位置
    if (!hashList[value]) {//第一次探测
        hashList[value] = 1;
        return value;
    }
    else {
        for (float searchTimes = 1; searchTimes < P; searchTimes++) {//P-1次探测
            int newValue = value;
            newValue = int(newValue + pow(-1, searchTimes - 1) * pow(ceil(searchTimes / 2), 2)) % P;
            if (newValue < 0)
                newValue += P;
            if (!hashList[newValue]) {
                hashList[newValue] = 1;
                return newValue;
            }
        }
        return -1;
    }
}

int main() {
    int N, P;
    cin >> N >> P;
    while (!is_prime_number(P))
        P++;
    int* hashList = (int*)malloc(P * sizeof(int));
    int result[10000] = { 0 };
    for (int i = 0; i < P; i++)
        hashList[i] = 0;
    for (int i = 0; i < N; i++) {
        char name[100];
        cin >> name;
        result[i] = hashLocation(hashList, generate_hash(name, P), P);
    }
    for (int i = 0; i < N; i++)
        if (result[i] == -1)
            cout << '-' << ' ';
        else cout << result[i] << ' ';
}

