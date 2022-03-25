#include <iostream>
using namespace std;

/*逆序对数实质就是插入排序过程中要移动元素的次数*/
/*移动的元素的位数即第一个序列中还未插入到新序列中的元素的个数*/

int merge(int* num, int left, int mid, int right){
    int* temp = new int[right - left + 1];
    int i = 0;
    int j = left;
    int k = mid + 1;
    int count = 0;
    while (j <= mid && k <= right){
        if (num[j] <= num[k])
            temp[i++] = num[j++];
        else{
            temp[i++] = num[k++];
            count += mid - j + 1;
        }
    }
    while (j <= mid){
        temp[i++] = num[j++];
    }
    while (k <= right){
        temp[i++] = num[k++];
    }

    for (int m = 0; m <= right - left; m++)
        num[left + m] = temp[m];
    delete[] temp;
    return count;
}

int mergeSort(int* num, int left, int right){
    if (left < right){
        int mid = (left + right) / 2;
        int n1 = mergeSort(num, left, mid);
        int n2 = mergeSort(num, mid + 1, right);
        int n3 = merge(num, left, mid, right);
        return n1 + n2 + n3;
    }
    return 0;
}

void loop(int len){
    int* arr = (int*)malloc(len * sizeof(int));
    for (int i = 0; i < len; i++)
        cin >> arr[i];
    cout << mergeSort(arr, 0, len - 1) << endl;
}

int main() {
    while (true){
        int len;
        cin >> len;
        if (!len)
            return 0;
        else loop(len);
    }
}