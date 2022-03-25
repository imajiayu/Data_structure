#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int arr[1000000];

int binarySearch(int length,int target) {//¶þ·Ö²éÕÒ
    int left = 0;
    int right = length - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }
    if (arr[left] == target) {
        return left;
    }
    return -1;
}

int main() {
	int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    int k;
    scanf("%d", &k);
	for (int i = 0; i < k; i++) {
        int target;
        scanf("%d", &target);
        printf("%d\n", binarySearch(n, target));
	}
	return 0;
}